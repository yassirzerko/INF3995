#ifndef SRC_STATEMACHINE_H_
#define SRC_STATEMACHINE_H_

#include "appData.h"
#include "median_filter.h"
#include "app_channel.h"
#include "math.h"
#include "SGBA.h"
#include "lowLevelCommands.h"
#include "estimator_kalman.h"

typedef enum
{
    // CrazyFlie should hover and has taken off
    STATE_A,

    // CrazyFlie should explore and has taken off
    STATE_B,

    // CrazyFlie should hover or explore but has not taken off yet
    STATE_C,

    // CrazyFlie should land  but is flying
    STATE_D,

    // CrazyFlie should land but is already on the ground
    STATE_E,

} ControlState;

void takeOff(struct AppData *appData);
void explorationMode(struct AppData *appData);
void executeLand(struct AppData *appData);
void stayOnGround(struct AppData *appData);
void initSGBA(int id, point_t initialPos);
void handleLastCommand(struct AppData *appData);
void handleCommunication(struct AppData *appData);
void setNextAction(struct AppData *appData);

ControlState getCurrentControlState(struct AppData *appData);

#endif
