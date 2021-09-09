#ifndef WALL_FOLLOWER_H
#define WALL_FOLLOWER_H

#include <argos3/core/control_interface/ci_controller.h>
/* Definition of the crazyflie position sensor */
#include <argos3/plugins/robots/generic/control_interface/ci_positioning_sensor.h>
/* Definition of the crazyflie position actuator */
#include <argos3/plugins/robots/generic/control_interface/ci_quadrotor_position_actuator.h>
/* Definition of the crazyflie distance sensor */
#include <argos3/plugins/robots/crazyflie/control_interface/ci_crazyflie_distance_scanner_sensor.h>
/* Definition of the Drone Commander class */
#include "commander.h"
/* Definition of the Distance Sensors Manager class */
#include "distance_sensors_manager.h"

using namespace argos;

enum WallFollowerState
{
    INIT = 0,
    START,
    WALL_ON_SIDE,
    ALIGNING,
    TURNING_AROUND,
    LOOKING_FOR_WALL
};

enum Mode
{
    NONE = 0,
    RIGHT,
    LEFT
};

const CRadians CORNER_VELOCITY = CRadians::PI / 100;
const Real NORMAL_VELOCITY = 0.08f;
const Real ALIGN_VELOCITY = 0.005f;
const Real TURN_AROUND_VELOCITY = 0.02f;
const UInt32 MIN_DISTANCE_BEFORE_CORNER = 30;
const UInt32 MAX_DISTANCE_LOOKING_WALL = 100;

class WallFollower
{

public:
    /* Class Contructor */
    WallFollower();
    /* Class Destructor */
    ~WallFollower() {}
    /* Initialize the Wall Follower */
    void Init(std::shared_ptr<Commander> commander,
              std::shared_ptr<DistanceSensorsManager> distance_manager);
    /* Execute The Wall Follower's Main Function */
    virtual bool Execute(CRadians &heading_angle) = 0;
    /* Find a New Heading Angle To Detach From The Wall */
    virtual bool SetNewHeading(CRadians &heading_angle) = 0;
    /* Keep Following The Wall Until It Ends */
    virtual bool KeepFollowingWall(CRadians &heading_angle) = 0;

protected:
    /* Handle The States Of The Algorithme */
    bool HandleStates(CRadians &heading_angle);
    /* Return True If The Drone Is Far From The Wall From The Side */
    bool IsWallFarFromSide();

    /* The Drone Commander */
    std::shared_ptr<Commander> m_commander;
    /* The Distance Sensors Manager */
    std::shared_ptr<DistanceSensorsManager> m_distance_manager;
    /* True If The Drone Is Changing Orientation */
    bool m_is_repositionning;
    /* Wall Follower's Dtate */
    WallFollowerState m_state;
    /* Wall Follower's Mode */
    Mode m_mode;
    /* Current Heading Angle */
    CRadians m_heading;
    /* Counter */
    UInt32 m_current_step;

private:
    /* Align The Drone On The Right Side Of The Wall */
    bool AlignRight();
    /* Align The Drone On The Left Side Of The Wall */
    bool AlignLeft();
    /* Turn The Drone Around The Corner */
    bool TurnAroundCorner(CRadians &heading_angle);
    /* Return True If The Drone Is Near The Corner */
    bool IsApproachingCorner();
    /* Go Straight Until You Find The Wall From The Side Of The Drone */
    bool LookForWallOnTheSide();
    /* Align To Start Following The Wall */
    bool StartFollowingWall(CRadians &heading_angle);
};

#endif
