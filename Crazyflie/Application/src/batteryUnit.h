#ifndef SRC_BATTERYUNIT_H_
#define SRC_BATTERYUNIT_H_
#include "pm.h"
#include "appData.h"

void setBatteryLevel(struct AppData *appData);
int getBatteryPercentage(double voltage);

#endif
