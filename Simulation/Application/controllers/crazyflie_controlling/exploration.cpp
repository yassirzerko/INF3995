#include "exploration.h"

/****************************************/
/****************************************/

Exploration::Exploration() : m_pc_RNG(CRandom::CreateRNG("argos")) {}

/****************************************/
/****************************************/

bool Exploration::Execute(CRadians &heading_angle)
{
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

bool Exploration::SetNewHeading(CRadians &heading_angle)
{
    if (m_mode != NONE)
    {
        srand(time(NULL));
        UInt64 seed = ((float)rand() / RAND_MAX) * 1000;
        m_pc_RNG->SetSeed(seed);
        m_pc_RNG->Reset();
        heading_angle += m_pc_RNG->Uniform(CRange<CRadians>(-CRadians::PI_OVER_FOUR, CRadians::PI_OVER_FOUR));
        heading_angle.UnsignedNormalize();
    }
    m_state = START;
    return true;
}

/****************************************/
/****************************************/

bool Exploration::KeepFollowingWall(CRadians &heading_angle)
{
    if (m_distance_manager->IsApproachingFromFront())
    {
        // Wall detected from Front!
        m_mode == RIGHT ? m_commander->TurnLeft(heading_angle) : m_commander->TurnRight(heading_angle);
        m_current_step = 0;
        return true;
    }
    if (!IsWallFarFromSide())
    {
        return false;
    }
    // std::cout << m_current_step << std::endl;
    if (m_current_step < MIN_DISTANCE_BEFORE_CORNER)
    {
        // Nothing is detected from the side but the distance we did is very short
        m_state = INIT;
        return false;
    }
    // Nothing detected from the side, we should turn around
    m_state = TURNING_AROUND;
    m_heading = heading_angle;
    m_heading += (m_mode == RIGHT ? -1 : 1) * CRadians::PI_OVER_TWO;
    m_heading.UnsignedNormalize();
    return false;
}

/****************************************/
/****************************************/
