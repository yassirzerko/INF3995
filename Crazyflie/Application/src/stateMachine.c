#include "stateMachine.h"
#include "debug.h"

const int readyBatteryLevelLimit = 30;
const int landBatteryLevelLimit = 10;

void setNextAction(struct AppData *appData)
{
    ControlState currentControlState = getCurrentControlState(appData);
    switch (currentControlState)
    {
    // CrazyFlie should hover and has taken off
    case STATE_A:
        appData->droneState = HOVERING;
        appData->vel_w_cmd = 0;
        hover(&appData->setpoint_BG, appData->nominal_height);
        break;

    // CrazyFlie should explore and has taken off
    case STATE_B:
        appData->droneState = appData->outbound ? EXPLORATING : RETURNING_TO_BASE;
        appData->vel_w_cmd = 0;
        hover(&appData->setpoint_BG, appData->nominal_height);
        explorationMode(appData);
        break;

    // CrazyFlie should hover or explore but has not taken off yet
    case STATE_C:
        takeOff(appData);
        appData->droneState = TAKING_OFF;
        break;

    // CrazyFlie should land  but is flying
    case STATE_D:
        executeLand(appData);
        appData->droneState = LANDING;
        break;

    // CrazyFlie should land but is already on the ground
    case STATE_E:
        stayOnGround(appData);
        appData->droneState = appData->batteryLevel <= readyBatteryLevelLimit ? NOT_READY : READY;
        break;

    default:
        break;
    }
}

void handleCommunication(struct AppData *appData)
{
    const int numberOfCommand = 4;
    if (appchannelReceivePacket(&appData->rxPacket, sizeof(appData->rxPacket), 0))
    {
        appData->lastCommand = appData->rxPacket.command < numberOfCommand ? appData->rxPacket.command : UNKNOWN_COMMAND;
    }
}

void handleLastCommand(struct AppData *appData)
{
    switch (appData->lastCommand)
    {
    case UNKNOWN_COMMAND:
        break;
    case LAND_COMMAND:
        appData->keep_flying = 0;
        appData->is_on_exploration_mode = 0;
        break;
    case START_EXPLORATION_COMMAND:
        if (appData->droneState == READY)
        {
            appData->keep_flying = 1;
            appData->is_on_exploration_mode = 1;
            appData->outbound = 1;
        }
        break;
    case TAKE_OFF_COMMAND:
        if (appData->droneState == READY)
        {
            appData->keep_flying = 1;
            appData->is_on_exploration_mode = 0;
        }
        break;
    case RETURN_TO_BASE_COMMAND:
        appData->outbound = 0;
        break;
    default:
        break;
    }

    appData->lastCommand = UNKNOWN_COMMAND;
}

void takeOff(struct AppData *appData)
{
    take_off(&appData->setpoint_BG, appData->nominal_height);
    if (appData->height > appData->nominal_height)
    {
        appData->taken_off = true;

        if (appData->is_on_exploration_mode)
        {
            initSGBA(appData->my_id, appData->initialPos);
        }
    }
    appData->on_the_ground = false;
}

void explorationMode(struct AppData *appData)
{
    bool priority = appData->id_inter_closest > appData->my_id;
    appData->state = SGBA_controller(&appData->vel_x_cmd, &appData->vel_y_cmd, &appData->vel_w_cmd, &appData->rssi_angle, &appData->state_wf, appData->front_range,
                                     appData->left_range, appData->right_range, appData->back_range, appData->heading_rad,
                                     (float)appData->pos.x, (float)appData->pos.y, appData->rssi_beacon_filtered, appData->rssi_inter_filtered, appData->rssi_angle_inter_closest, priority, appData->outbound, &appData->keep_flying);

    memcpy(&appData->p_reply.data[1], &appData->rssi_angle, sizeof(float));

    float vel_w_cmd_convert = appData->vel_w_cmd * 180.0f / (float)M_PI;
    vel_command(&appData->setpoint_BG, appData->vel_x_cmd, appData->vel_y_cmd, vel_w_cmd_convert, appData->nominal_height);
    appData->on_the_ground = false;
}

void executeLand(struct AppData *appData)
{
    land(&appData->setpoint_BG, 0.2f);
    if (appData->height < 0.1f)
    {
        shut_off_engines(&appData->setpoint_BG);
        appData->taken_off = false;
    }
    appData->on_the_ground = false;
}

void stayOnGround(struct AppData *appData)
{
    shut_off_engines(&appData->setpoint_BG);
    appData->takeoffdelaytime = usecTimestamp();
    appData->on_the_ground = true;
    appData->taken_off = false;
}

void initSGBA(int id, point_t initialPos)
{
    const float newDistanceFromWall = 0.4;
    const float maxSpeed = 0.5;

    //Default value
    float wantedHeading = 0.8;

    if (id == 4 || id == 8)
    {
        wantedHeading = -0.8;
    }
    else if (id == 3 || id == 7)
    {
        wantedHeading = -2.4;
    }
    else if (id == 5 || id == 9)
    {
        wantedHeading = 2.4;
    }

    init_SGBA_controller(newDistanceFromWall, maxSpeed, wantedHeading, initialPos.x, initialPos.y);
}

ControlState getCurrentControlState(struct AppData *appData)
{
    const int counterTreshHold = 500;
    // Drone should returnToBase
    if (appData->batteryLevel <= readyBatteryLevelLimit && appData->taken_off)
    {
        appData->batteryCounter += 1;
        if (appData->batteryCounter >= counterTreshHold)
        {
            appData->outbound = 0;
        }
    }
    else
    {
        appData->batteryCounter = 0;
    }

    //Drone should land
    if (appData->batteryLevel <= landBatteryLevelLimit)
    {
        appData->batteryCounter += 1;
        if (appData->batteryCounter >= counterTreshHold)
        {
            appData->keep_flying = 0;
            appData->is_on_exploration_mode = 0;
        }
    }
    else
    {
        appData->batteryCounter = 0;
    }

    if (appData->keep_flying && appData->taken_off)
    {
        if (!appData->is_on_exploration_mode)
        {
            return STATE_A;
        }
        return STATE_B;
    }

    if (appData->keep_flying && !appData->taken_off)
    {
        return STATE_C;
    }

    if (!appData->keep_flying)
    {
        if (appData->taken_off)
        {
            return STATE_D;
        }
        return STATE_E;
    }

    return STATE_E;
}
