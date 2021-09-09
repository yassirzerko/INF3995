#ifndef SRC_ROUTINE_H_
#define SRC_ROUTINE_H_

#include "string.h"
#include "estimator_kalman.h"
#include "appData.h"
#include "log.h"
#include "configblock.h"
#include "range.h"
#include "math.h"
#include "param.h"
#include "utils.h"
#include "batteryUnit.h"

void updateMultiRangerValues(struct AppData *appData);
void updateRSSI(struct AppData *appData);
void updateSensorsData(struct AppData *appData);

#endif
