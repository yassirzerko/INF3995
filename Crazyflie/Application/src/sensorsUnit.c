#include "sensorsUnit.h"

bool areInitialPosSet = false;
void updateMultiRangerValues(struct AppData *appData)
{
    // Select which laser range sensor readings to use
    appData->multiranger_isinit = paramGetInt(getParamId(MULTIRANGER));
    if (appData->multiranger_isinit)
    {
        appData->front_range = (float)rangeGet(rangeFront) / 1000.0f;
        appData->right_range = (float)rangeGet(rangeRight) / 1000.0f;
        appData->left_range = (float)rangeGet(rangeLeft) / 1000.0f;
        appData->back_range = (float)rangeGet(rangeBack) / 1000.0f;
        appData->up_range = (float)rangeGet(rangeUp) / 1000.0f;
    }
}

void updateRSSI(struct AppData *appData)
{
    // For every 1 second, reset the RSSI value to high if it hasn't been received for a while
    for (uint8_t it = 0; it < 9; it++)
        if (usecTimestamp() >= appData->time_array_other_drones[it] + 1000 * 1000)
        {
            appData->time_array_other_drones[it] = usecTimestamp() + 1000 * 1000 + 1;
            appData->rssi_array_other_drones[it] = 150;
            appData->rssi_angle_array_other_drones[it] = 500.0f;
        }

    // get RSSI, id and angle of closests crazyflie.
    appData->id_inter_closest = (uint8_t)find_minimum(appData->rssi_array_other_drones, 9);
    appData->rssi_inter_closest = appData->rssi_array_other_drones[appData->id_inter_closest];
    appData->rssi_angle_inter_closest = appData->rssi_angle_array_other_drones[appData->id_inter_closest];

    // filter rssi
    appData->rssi_inter_filtered = (uint8_t)update_median_filter_f(&appData->medFilt_2, (float)appData->rssi_inter_closest);

    //t RSSI of beacon
    appData->rssi_beacon = logGetFloat(getLogId(2));
    appData->rssi_beacon_filtered = (uint8_t)update_median_filter_f(&appData->medFilt_3, (float)appData->rssi_beacon);
}

void updateSensorsData(struct AppData *appData)
{

    updateRSSI(appData);

    updateMultiRangerValues(appData);

    setBatteryLevel(appData);
    // get current height and heading
    appData->height = logGetFloat(getLogId(0));
    float heading_deg = logGetFloat(getLogId(1));
    appData->heading_rad = heading_deg * (float)M_PI / 180.0f;

    // Get position estimate of kalman filter
    estimatorKalmanGetEstimatedPos(&appData->pos);

    if (!areInitialPosSet)
    {
        estimatorKalmanGetEstimatedPos(&appData->initialPos);
        areInitialPosSet = true;
    }

    // Initialize setpoint
    memset(&appData->setpoint_BG, 0, sizeof(appData->setpoint_BG));

    // Filtere uprange, since it sometimes gives a low spike that
    appData->flowdeck_isinit = paramGetUint(getParamId(FLOWDECK));
    appData->up_range_filtered = update_median_filter_f(&appData->medFilt, appData->up_range);
    if (appData->up_range_filtered < 0.05f)
    {
        appData->up_range_filtered = appData->up_range;
    }

    appData->correctly_initialized = appData->flowdeck_isinit && appData->multiranger_isinit;

    if (appData->keep_flying && (!appData->correctly_initialized || appData->up_range < 0.2f))
    {
        appData->keep_flying = 0;
        appData->is_on_exploration_mode = 0;
    }
    appData->state = 0;
}
