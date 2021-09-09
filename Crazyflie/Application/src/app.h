#ifndef SRC_APP_H_
#define SRC_APP_H_

#include <string.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "log.h"
#include "system.h"
#include "sensors.h"
#include "stabilizer_types.h"
#include "stabilizer.h"
#include "usec_time.h"
#include "median_filter.h"
#include "configblock.h"
#include "radiolink.h"
#include "commander.h"
#include "led.h"
#include "appData.h"
#include "sensorsUnit.h"
#include "stateMachine.h"

void p2pcallbackHandler(P2PPacket *p);
static void initReply();
void initApp();

#endif
