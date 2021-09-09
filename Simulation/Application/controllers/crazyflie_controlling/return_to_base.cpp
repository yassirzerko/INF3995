#include "return_to_base.h"

/****************************************/
/****************************************/

ReturnToBase::ReturnToBase()
{
    m_is_repositionning = false;
}

/****************************************/
/****************************************/

bool ReturnToBase::Execute(CRadians &heading_angle)
{
    if (GetDistanceFrom(BASE_STATION) < 1.0f)
    {
        return true;
    }
    m_distance_manager->UpdateSensorsData();
    if (m_is_repositionning)
    {
        m_is_repositionning = !m_commander->SetOrientation(heading_angle);
        return false;
    }
    m_is_repositionning = HandleStates(heading_angle);
    return false;
}

/****************************************/
/****************************************/

bool ReturnToBase::SetNewHeading(CRadians &heading_angle)
{
    if (IsDirectionToTargetPossible(BASE_STATION) || m_mode == NONE)
    {
        heading_angle = GetNewHeadingToTarget(BASE_STATION);
        m_state = START;
        return true;
    }
    m_state = TURNING_AROUND;
    m_heading = heading_angle;
    m_heading += (m_mode == RIGHT ? -1 : 1) * CRadians::PI_OVER_TWO;
    m_heading.UnsignedNormalize();
    return false;
}

/****************************************/
/****************************************/

bool ReturnToBase::KeepFollowingWall(CRadians &heading_angle)
{
    if (m_distance_manager->IsApproachingFromFront())
    {
        // Wall detected from Front!
        m_mode == RIGHT ? m_commander->TurnLeft(heading_angle) : m_commander->TurnRight(heading_angle);
        return true;
    }
    if (!IsWallFarFromSide())
    {
        return false;
    }
    m_state = INIT;
    return false;
}

/****************************************/
/****************************************/

Real ReturnToBase::GetDistanceFrom(CVector2 target)
{
    CVector3 pos3D = m_commander->GetCurrentPosition();
    CVector2 pos2D = CVector2(pos3D.GetX(), pos3D.GetY());
    return (target - pos2D).Length();
}

/****************************************/
/****************************************/

bool ReturnToBase::IsDirectionToTargetPossible(CVector2 target)
{
    CVector3 pos3D = m_commander->GetCurrentPosition();
    CVector2 pos2D = CVector2(pos3D.GetX(), pos3D.GetY());
    CVector3 orientation3D = m_commander->GetCurrentOrientation();
    CVector2 orientation2D = CVector2(orientation3D.GetX(), orientation3D.GetY());
    return orientation2D.DotProduct(target - pos2D) > 0.0f;
}

/****************************************/
/****************************************/

CRadians ReturnToBase::GetNewHeadingToTarget(CVector2 target)
{
    CVector3 pos3D = m_commander->GetCurrentPosition();
    CVector2 pos2D = CVector2(pos3D.GetX(), pos3D.GetY());
    return (target - pos2D).Angle().UnsignedNormalize();
}

/****************************************/
/****************************************/
