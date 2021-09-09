#ifndef COMMANDER_H
#define COMMANDER_H

#include <argos3/core/control_interface/ci_controller.h>
/* Definition of the crazyflie position sensor */
#include <argos3/plugins/robots/generic/control_interface/ci_positioning_sensor.h>
/* Definition of the crazyflie position actuator */
#include <argos3/plugins/robots/generic/control_interface/ci_quadrotor_position_actuator.h>

using namespace argos;

const CVector3 GO_RIGHT = CVector3(0.0f, 1.0f, 0.0f).Normalize();
const CVector3 GO_LEFT = CVector3(0.0f, -1.0f, 0.0f).Normalize();
const CVector3 GO_STRAIGHT = CVector3(1.0f, 0.0f, 0.0f).Normalize();
const CRadians ANGLE_ERROR = CRadians::PI / 100;

class Commander
{
public:
    /* Class Contructor */
    Commander();
    /* Class Destructor */
    ~Commander() {}
    /* Initialize the Drone Commander */
    void Init(CCI_QuadRotorPositionActuator *pc_propellers, CCI_PositioningSensor *pc_pos, CRadians current_angle);
    /* Take Off */
    void TakeOff(Real height);
    /* Land The Drone On The Ground */
    void Land();
    /* Go Straight */
    void MoveForward(Real velocity);
    /* Move To The Right Without Rotating (Translating) */
    void MoveRight(Real velocity);
    /* Move To The Left Without Rotating (Translating) */
    void MoveLeft(Real velocity);
    /* Return True If The Orientation Of The Drone Is At angle */
    bool IsAtAngle(CRadians angle);
    /* Change The Orientation Of The Drone Step By Step */
    bool SetOrientation(CRadians target_angle);
    /* Change The Orientation of The Drone Immediately */
    void SetImmediateOrientation(CRadians target_angle);
    /* Turn 90 Derges To The Right */
    void TurnLeft(CRadians &heading_angle);
    /* Turn 90 Derges To The Right */
    void TurnRight(CRadians &heading_angle);
    /* Set The m_current_angle Attribute To angle */
    void SetCurrentOrientation(CRadians angle);
    /* Update The m_current_angle Attribute */
    void UpdateCurrentAngle();
    /* Get The Current Position Of The Drone */
    CVector3 GetCurrentPosition();
    /* Get The Current Orientation Vector Of The Drone */
    CVector3 GetCurrentOrientation();

private:
    /* Pointer To The Position Actuator */
    CCI_QuadRotorPositionActuator *m_pc_propellers;
    /* Pointer To The Positioning Sensor */
    CCI_PositioningSensor *m_pc_pos;
    /* Current angle */
    CRadians m_current_angle;
};

#endif
