#include "batteryUnit.h"
#include "debug.h"

float voltageTresholds[] = {
    4.20F, // 100 %
    4.15F, // 95  %
    4.11F, // 90  %
    4.08F, // 85  %
    4.02F, // 80  %
    3.98F, // 75  %
    3.95F, // 70  %
    3.91F, // 65  %
    3.87F, // 60  %
    3.85F, // 55  %
    3.84F, // 50  %
    3.82F, // 45  %
    3.80F, // 40  %
    3.79F, // 35  %
    3.77F, // 30  %
    3.75F, // 25  %
    3.73F, // 20  %
    3.71F, // 15  %
    3.69F, // 10  %
    3.61F, // 5   %
    3.27F, // 0   %
};

void setBatteryLevel(struct AppData *appData)
{
    double voltage = pmGetBatteryVoltage();
    if (!appData->on_the_ground)
    {
        // The voltage level is poorly estimated when the drones are no longer on the ground
        const double voltageAdjustement = 0.35f;
        voltage += voltageAdjustement;
    }
    appData->batteryLevel = getBatteryPercentage(voltage);
}

int getBatteryPercentage(double voltage)
{
    size_t nTresholds = 21;
    float fullBatteryLevel = 100.0F;
    float emptyBatteryLevel = 0.0F;
    float percentageOfVariationPerTreshold = 5;

    if (voltage > (double)voltageTresholds[0])
    {
        return fullBatteryLevel;
    }
    if ((double)voltageTresholds[nTresholds - 1] > voltage)
    {
        return emptyBatteryLevel;
    }

    size_t currentTreshold = nTresholds - 1;
    while (voltage > (double)voltageTresholds[currentTreshold])
    {
        currentTreshold--;
    }

    int difference = (nTresholds - 1) - currentTreshold;
    return difference * percentageOfVariationPerTreshold;
}
