#include "commander.h"

Commander::Commander() : m_pc_propellers(NULL),
                         m_pc_pos(NULL),
                         m_current_angle(CRadians::ZERO) {}

/****************************************/
/****************************************/

void Commander::Init(CCI_QuadRotorPositionActuator *pc_propellers, CCI_PositioningSensor *pc_pos, CRadians current_angle)
{
    m_pc_propellers = pc_propellers;
    m_pc_pos = pc_pos;
    m_current_angle = current_angle;
}

/****************************************/
/****************************************/

void Commander::TakeOff(Real height)
{
    m_pc_propellers->SetRelativePosition(CVector3(0.0f, 0.0f, height));
    UpdateCurrentAngle();
}

/****************************************/
/****************************************/

void Commander::Land()
{
    Real posZ = -m_pc_pos->GetReading().Position.GetZ() + 0.1f;
    m_pc_propellers->SetRelativePosition(CVector3(0.0f, 0.0f, posZ));
}

/****************************************/
/****************************************/

void Commander::MoveForward(Real velocity)
{
    m_pc_propellers->SetRelativePosition(velocity * GO_STRAIGHT);
}

/****************************************/
/****************************************/

void Commander::MoveRight(Real velocity)
{
    m_pc_propellers->SetRelativePosition(velocity * GO_RIGHT);
}

/****************************************/
/****************************************/

void Commander::MoveLeft(Real velocity)
{
    m_pc_propellers->SetRelativePosition(velocity * GO_LEFT);
}

/****************************************/
/****************************************/

bool Commander::IsAtAngle(CRadians angle)
{
    CRadians currentAngle;
    CVector3 vector(0.0f, 0.0f, 1.0f);
    m_pc_pos->GetReading().Orientation.ToAngleAxis(currentAngle, vector);
    return Abs(angle - currentAngle) < CRadians::PI / 100;
}

/****************************************/
/****************************************/

bool Commander::SetOrientation(CRadians target_angle)
{
    // Don't change orientation unless you are at m_current_angle
    if (!IsAtAngle(m_current_angle))
        return target_angle == m_current_angle;

    if (target_angle == m_current_angle)
        return true;

    if (Abs(m_current_angle - target_angle) > ANGLE_ERROR)
    {
        // Initialize the step
        CRadians step = (target_angle - m_current_angle) / 10;
        // Change the orientation by the defined step
        m_pc_propellers->SetRelativeYaw(step);
        m_current_angle += step;
    }
    else
    {
        // Finalize the rotating process
        m_pc_propellers->SetRelativeYaw(target_angle - m_current_angle);
        m_current_angle = target_angle;
    }
    return false;
}

/****************************************/
/****************************************/

void Commander::SetImmediateOrientation(CRadians target_angle)
{
    m_pc_propellers->SetRelativeYaw(target_angle);
}

/****************************************/
/****************************************/

void Commander::TurnRight(CRadians &heading_angle)
{
    int nTimes = heading_angle / CRadians::PI_OVER_TWO;
    CRadians difference = heading_angle - nTimes * CRadians::PI_OVER_TWO;
    heading_angle += difference != CRadians::ZERO ? CRadians::PI_OVER_TWO - difference : CRadians::ZERO;
    heading_angle -= CRadians::PI_OVER_TWO;
    heading_angle.UnsignedNormalize();
}

/****************************************/
/****************************************/

void Commander::TurnLeft(CRadians &heading_angle)
{
    int nTimes = heading_angle / CRadians::PI_OVER_TWO;
    CRadians difference = heading_angle - nTimes * CRadians::PI_OVER_TWO;
    heading_angle += difference != CRadians::ZERO ? -difference : CRadians::ZERO;
    heading_angle += CRadians::PI_OVER_TWO;
    heading_angle.UnsignedNormalize();
}

/****************************************/
/****************************************/

void Commander::SetCurrentOrientation(CRadians angle)
{
    m_current_angle = angle;
}

/****************************************/
/****************************************/

void Commander::UpdateCurrentAngle()
{
    CVector3 vector(0.0f, 0.0f, 1.0f);
    m_pc_pos->GetReading().Orientation.ToAngleAxis(m_current_angle, vector);
    m_current_angle.UnsignedNormalize();
}

/****************************************/
/****************************************/

CVector3 Commander::GetCurrentPosition()
{
    return m_pc_pos->GetReading().Position;
}

/****************************************/
/****************************************/

CVector3 Commander::GetCurrentOrientation()
{
    CRadians currentAngle;
    CVector3 vector(0.0f, 0.0f, 1.0f);
    m_pc_pos->GetReading().Orientation.ToAngleAxis(currentAngle, vector);
    return CVector3(Cos(currentAngle), Sin(currentAngle), 0.0f);
}

/****************************************/
/****************************************/
