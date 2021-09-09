/* Include the WallFollower class definition */
#include "wall_follower.h"

/****************************************/
/****************************************/

WallFollower::WallFollower() : m_state(INIT),
                               m_mode(NONE),
                               m_heading(),
                               m_is_repositionning(true),
                               m_commander(NULL),
                               m_distance_manager(NULL),
                               m_current_step(0) {}

/****************************************/
/****************************************/

void WallFollower::Init(std::shared_ptr<Commander> commander,
                        std::shared_ptr<DistanceSensorsManager> distance_manager)
{
    m_commander = commander;
    m_distance_manager = distance_manager;
}

/****************************************/
/****************************************/

bool WallFollower::HandleStates(CRadians &heading_angle)
{
    switch (m_state)
    {
    case INIT:
        return SetNewHeading(heading_angle);

    case START:
        if (StartFollowingWall(heading_angle))
        {
            return true;
        }
        break;

    case WALL_ON_SIDE:
        if (KeepFollowingWall(heading_angle))
        {
            return true;
        }
        m_current_step++;
        break;

    case ALIGNING:
        return m_mode == RIGHT ? AlignRight() : AlignLeft();

    case TURNING_AROUND:
        return TurnAroundCorner(heading_angle);

    case LOOKING_FOR_WALL:
        return LookForWallOnTheSide();
    }
    m_commander->MoveForward(NORMAL_VELOCITY);
    return false;
}

/****************************************/
/****************************************/

bool WallFollower::AlignLeft()
{
    if (m_distance_manager->IsFarFromWall(LEFT_DIRECTION))
    {
        m_state = INIT;
        return false;
    }
    if (m_distance_manager->ShouldAlighToLeft(false))
    {
        m_commander->MoveLeft(ALIGN_VELOCITY);
        return false;
    }
    if (m_distance_manager->ShouldAlighToRight(false))
    {
        m_commander->MoveRight(ALIGN_VELOCITY);
        return false;
    }
    m_state = WALL_ON_SIDE;
    m_mode = LEFT;
    m_current_step = 0;
    return false;
}

/****************************************/
/****************************************/

bool WallFollower::AlignRight()
{
    if (m_distance_manager->IsFarFromWall(RIGHT_DIRECTION))
    {
        m_state = INIT;
        return false;
    }
    if (m_distance_manager->ShouldAlighToRight(true))
    {
        m_commander->MoveRight(ALIGN_VELOCITY);
        return false;
    }
    if (m_distance_manager->ShouldAlighToLeft(true))
    {
        m_commander->MoveLeft(ALIGN_VELOCITY);
        return false;
    }
    m_state = WALL_ON_SIDE;
    m_mode = RIGHT;
    m_current_step = 0;
    return false;
}

/****************************************/
/****************************************/

bool WallFollower::TurnAroundCorner(CRadians &heading_angle)
{
    if (m_commander->IsAtAngle(m_heading))
    {
        // We've finished turning around the corner
        m_mode == RIGHT ? m_commander->TurnRight(heading_angle) : m_commander->TurnLeft(heading_angle);
        m_commander->SetCurrentOrientation(m_heading);
        m_state = LOOKING_FOR_WALL;
        m_current_step = 0;
        return true;
    }
    // We're still turning around the corner
    if (IsApproachingCorner())
    {
        // Move a bit further fron the corner
        m_commander->MoveForward(TURN_AROUND_VELOCITY);
    }
    else
    {
        // Keep turning
        m_commander->SetImmediateOrientation((m_mode == RIGHT ? -1 : 1) * CORNER_VELOCITY);
    }
    return false;
}

/****************************************/
/****************************************/

bool WallFollower::IsWallFarFromSide()
{
    return m_distance_manager->IsFarFromWall(m_mode == RIGHT ? RIGHT_DIRECTION : LEFT_DIRECTION);
}

/****************************************/
/****************************************/

bool WallFollower::IsApproachingCorner()
{
    return m_distance_manager->IsApproachingCorner(m_mode == RIGHT ? RIGHT_DIRECTION : LEFT_DIRECTION);
}

/****************************************/
/****************************************/

bool WallFollower::LookForWallOnTheSide()
{
    if (m_current_step > MAX_DISTANCE_LOOKING_WALL)
    {
        m_state = INIT;
        return false;
    }
    if (IsWallFarFromSide())
    {
        // We're npt detecting the wall, we should go straight until we find it
        m_commander->MoveForward(TURN_AROUND_VELOCITY);
        m_current_step++;
        return false;
    }
    m_state = ALIGNING;
    return false;
}

/****************************************/
/****************************************/

bool WallFollower::StartFollowingWall(CRadians &heading_angle)
{
    if (m_distance_manager->IsApproachingFromLeft())
    {
        m_commander->TurnRight(heading_angle);
        m_state = WALL_ON_SIDE;
        m_current_step = 0;
        m_mode = LEFT;
        return true;
    }
    if (m_distance_manager->IsApproachingFromRight())
    {
        m_commander->TurnLeft(heading_angle);
        m_state = WALL_ON_SIDE;
        m_current_step = 0;
        m_mode = RIGHT;
        return true;
    }
    if (m_distance_manager->IsApproachingFromFront())
    {
        m_commander->TurnLeft(heading_angle);
        m_state = WALL_ON_SIDE;
        m_current_step = 0;
        m_mode = RIGHT;
        return true;
    }
    return false;
}

/****************************************/
/****************************************/
