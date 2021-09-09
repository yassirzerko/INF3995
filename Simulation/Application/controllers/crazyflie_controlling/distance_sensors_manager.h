#ifndef DISTANCE_SENSORS_MANAGER_H
#define DISTANCE_SENSORS_MANAGER_H

#include <argos3/core/control_interface/ci_controller.h>
/* Definition of the crazyflie distance sensor */
#include <argos3/plugins/robots/crazyflie/control_interface/ci_crazyflie_distance_scanner_sensor.h>

using namespace argos;

const Real MIN_OUT_OF_RANGE = -1.0f;
const Real MAX_OUT_OF_RANGE = 40.0f;
const Real MIN_THRESHHOLD_WALL = 0.0f;
const Real MAX_THRESHHOLD_WALL = 30.0f;
const Real MIN_ALIGNING_WALL = 10.0f;
const Real MAX_ALIGNING_WALL = 25.0f;
const Real MIN_THRESHHOLD_CORNER = 0.0f;
const Real MAX_THRESHHOLD_CORNER = 25.0f;
const Real SIDE_WALL_THRESHHOLD = 70.0f;
const Real FAR_DISTANCE = -2.0f;
const UInt8 N_DIRECTIONS = 4;

enum Direction
{
    FRONT_DIRECTION = 0,
    LEFT_DIRECTION,
    BACK_DIRECTION,
    RIGHT_DIRECTION
};

class DistanceSensorsManager
{
public:
    /* Class Contructor */
    DistanceSensorsManager();
    /* Class Destructor */
    ~DistanceSensorsManager(){};
    /* Initialize the Distance Sensors Manager */
    void Init(CCI_CrazyflieDistanceScannerSensor *pc_distance);
    /* Update The Attribute m_sDist */
    void UpdateSensorsData();
    /* Get The Front Sensor's Data */
    Real GetFrontDistance();
    /* Get The Right Sensor's Data */
    Real GetRightDistance();
    /* Get The Left Sensor's Data */
    Real GetLeftDistance();
    /* Get The Back Sensor's Data */
    Real GetBackDistance();
    /* Return True If The Drone Is Far From The Wall From The Direction "direction" */
    bool IsFarFromWall(Direction direction);
    /* Return True If The Drone Is Approaching The Wall From The Front */
    bool IsApproachingFromFront();
    /* Return True If The Drone Is Approaching The Wall From The Right */
    bool IsApproachingFromRight();
    /* Return True If The Drone Is Approaching The Wall From The Left */
    bool IsApproachingFromLeft();
    /* Return True If The Drone Should Be Aligning A Bit To The Right */
    bool ShouldAlighToRight(bool right);
    /* Return True If The Drone Should Be Aligning A Bit To The Left */
    bool ShouldAlighToLeft(bool right);
    /* Return True If The Drone Is Getting Near The Corner From The Right */
    bool IsApproachingCorner(Direction direction);
    /* Return True If The Drone Is Getting Near The Corner From The Left */
    bool IsApproachingLeftCorner();

private:
    /* Pointer To The Crazyflie Distance Sensor */
    CCI_CrazyflieDistanceScannerSensor *m_pc_distance;
    /* Map Of The Distance Sensors Data */
    CCI_CrazyflieDistanceScannerSensor::TReadingsMap m_dist_reading;
};

#endif
