#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include "param.h"

static inline int32_t find_minimum(uint8_t a[], int32_t n)
{
    int32_t c, min, index;

    min = a[0];
    index = 0;

    for (c = 1; c < n; c++)
    {
        if (a[c] < min)
        {
            index = c;
            min = a[c];
        }
    }

    return index;
}

// Todo : mettre ca dans un autre fichier
static inline void init_median_filters_f(struct MedianFilterFloat *filter_1, struct MedianFilterFloat *filter_2, struct MedianFilterFloat *filter_3)
{
    init_median_filter_f(filter_1, 5);
    init_median_filter_f(filter_2, 5);
    init_median_filter_f(filter_3, 13);
}

typedef enum
{
    MULTIRANGER,
    FLOWDECK,
    VBAT,

} Param;

static inline paramVarId_t getParamId(Param param)
{
    paramVarId_t varid;
    switch (param)
    {
    //multiranger
    case MULTIRANGER:
        varid = paramGetVarId("deck", "bcMultiranger");
        break;

    // flowdeck
    case FLOWDECK:
        varid = paramGetVarId("deck", "bcFlow2");
        break;

    //battery
    case VBAT:
        varid = paramGetVarId("pm", "vbat");
    default:
        return varid;
    }
    return varid;
}

static inline logVarId_t getLogId(int param)
{
    logVarId_t varid;
    switch (param)
    {
    //height
    case 0:
        varid = logGetVarId("kalman", "stateZ");
        break;

    //heading deg
    case 1:
        varid = logGetVarId("stabilizer", "yaw");
        break;

    // rssi of beacon
    case 2:
        varid = logGetVarId("radio", "rssi");
        break;

    default:
        return varid;
    }
    return varid;
}

#endif
