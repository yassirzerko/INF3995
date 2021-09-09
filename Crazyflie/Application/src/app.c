/*
 * gradient_bug.c
 *
 *  Created on: Aug 9, 2018
 *      Author: knmcguire
 *  Modified by : 
 *      Mohamed Yassir El Aoufir
 */

#include "app.h"
#define MANUAL_STARTUP_TIMEOUT M2T(3000)

struct AppData appData;

void appMain(void *param)
{
    initApp();

    while (1)
    {
        handleLastCommand(&appData);
        vTaskDelay(10);
        updateSensorsData(&appData);
        setNextAction(&appData);
        commanderSetSetpoint(&appData.setpoint_BG, 3);
        handleCommunication(&appData);
    }
}

void initApp()
{
    init_median_filters_f(&appData.medFilt, &appData.medFilt_2, &appData.medFilt_3);
    // init p2p
    p2pRegisterCB(p2pcallbackHandler);
    P2PPacket p_reply;
    initReply(&p_reply);

    memcpy(&p_reply.data[1], &appData.rssi_angle, sizeof(float));

    appData.takeoffdelaytime = 0;
    appData.keep_flying = false;
    appData.taken_off = false;
    appData.on_the_ground = true;
    appData.correctly_initialized = false;
    appData.is_on_exploration_mode = false;
    appData.nominal_height = 0.3;
    appData.outbound = true;
    appData.batteryCounter = 0;

    for (int i = 0; i < 9; i++)
    {
        appData.rssi_angle_array_other_drones[i] = 150;
        appData.time_array_other_drones[i] = 0;
        appData.rssi_angle_array_other_drones[i] = 500.0f;
    }

    appData.id_inter_closest = 100;
    appData.lastCommand = UNKNOWN_COMMAND;
    appData.droneState = READY;

    systemWaitStart();
    vTaskDelay(M2T(3000));
}

void p2pcallbackHandler(P2PPacket *p)
{
    appData.id_inter_ext = p->data[0];
    appData.rssi_inter = p->rssi;
    memcpy(&appData.rssi_angle_inter_ext, &p->data[1], sizeof(float));

    appData.rssi_array_other_drones[appData.id_inter_ext] = appData.rssi_inter;
    appData.time_array_other_drones[appData.id_inter_ext] = usecTimestamp();
    appData.rssi_angle_array_other_drones[appData.id_inter_ext] = appData.rssi_angle_inter_ext;
}

static void initReply()
{
    appData.address = configblockGetRadioAddress();
    appData.my_id = (uint8_t)((appData.my_id) & 0x00000000ff);

    appData.p_reply.port = 0x00;
    appData.p_reply.data[0] = appData.my_id;
    appData.p_reply.size = 5;
}

LOG_GROUP_START(drone)
LOG_ADD(LOG_UINT8, droneState, &appData.droneState)
LOG_ADD(LOG_UINT16, batteryLevel, &appData.batteryLevel)
LOG_ADD(LOG_FLOAT, initX, &appData.initialPos.x)
LOG_ADD(LOG_FLOAT, initY, &appData.pos.x)
LOG_GROUP_STOP(drone)
