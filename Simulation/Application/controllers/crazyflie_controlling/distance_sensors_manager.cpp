#include "distance_sensors_manager.h"

DistanceSensorsManager::DistanceSensorsManager() : m_pc_distance(NULL) {}

/****************************************/
/****************************************/

void DistanceSensorsManager::Init(CCI_CrazyflieDistanceScannerSensor *pc_distance)
{
    m_pc_distance = pc_distance;
}

/****************************************/
/****************************************/

void DistanceSensorsManager::UpdateSensorsData()
{
    m_dist_reading = m_pc_distance->GetReadingsMap();
}

/****************************************/
/****************************************/

Real DistanceSensorsManager::GetFrontDistance()
{
    auto iter_dist_read = m_dist_reading.begin();
    if (m_dist_reading.size() == N_DIRECTIONS)
    {
        iter_dist_read++;
        return iter_dist_read->second;
    }
    return FAR_DISTANCE;
}

/****************************************/
/****************************************/

Real DistanceSensorsManager::GetBackDistance()
{
    auto iter_dist_read = m_dist_reading.begin();
    if (m_dist_reading.size() == N_DIRECTIONS)
    {
        iter_dist_read++;
        iter_dist_read++;
        iter_dist_read++;
        return iter_dist_read->second;
    }
    return FAR_DISTANCE;
}

/****************************************/
/****************************************/

Real DistanceSensorsManager::GetLeftDistance()
{
    auto iter_dist_read = m_dist_reading.begin();
    if (m_dist_reading.size() == N_DIRECTIONS)
    {
        iter_dist_read++;
        iter_dist_read++;
        return iter_dist_read->second;
    }
    return FAR_DISTANCE;
}

/****************************************/
/****************************************/

Real DistanceSensorsManager::GetRightDistance()
{
    auto iter_dist_read = m_dist_reading.begin();
    if (m_dist_reading.size() == N_DIRECTIONS)
    {
        return iter_dist_read->second;
    }
    return FAR_DISTANCE;
}

/****************************************/
/****************************************/

bool DistanceSensorsManager::IsFarFromWall(Direction direction)
{
    Real distance = FAR_DISTANCE;
    switch (direction)
    {
    case FRONT_DIRECTION:
        distance = GetFrontDistance();
        return distance > MAX_OUT_OF_RANGE || distance < MIN_OUT_OF_RANGE;

    case LEFT_DIRECTION:
        distance = GetLeftDistance();
        return distance > MAX_OUT_OF_RANGE || distance < MIN_OUT_OF_RANGE;

    case BACK_DIRECTION:
        distance = GetBackDistance();
        return distance > MAX_OUT_OF_RANGE || distance < MIN_OUT_OF_RANGE;

    case RIGHT_DIRECTION:
        distance = GetRightDistance();
        return distance > MAX_OUT_OF_RANGE || distance < MIN_OUT_OF_RANGE;
    }
}

/****************************************/
/****************************************/

bool DistanceSensorsManager::IsApproachingFromFront()
{
    Real distance = GetFrontDistance();
    return distance < MAX_THRESHHOLD_WALL && distance > MIN_THRESHHOLD_WALL;
}

/****************************************/
/****************************************/

bool DistanceSensorsManager::IsApproachingFromRight()
{
    Real front_distance = GetFrontDistance();
    Real right_distance = GetRightDistance();
    front_distance = front_distance < MIN_OUT_OF_RANGE || front_distance > SIDE_WALL_THRESHHOLD ? 0.0f : front_distance;
    right_distance = right_distance < MIN_OUT_OF_RANGE ? 0.0f : right_distance;
    Real distance = (front_distance * right_distance) / hypot(front_distance, right_distance);
    return distance < MAX_THRESHHOLD_WALL && distance > MIN_THRESHHOLD_WALL;
}

/****************************************/
/****************************************/

bool DistanceSensorsManager::IsApproachingFromLeft()
{
    Real front_distance = GetFrontDistance();
    Real left_distance = GetLeftDistance();
    front_distance = front_distance < MIN_OUT_OF_RANGE || front_distance > SIDE_WALL_THRESHHOLD ? 0.0f : front_distance;
    left_distance = left_distance < MIN_OUT_OF_RANGE ? 0.0f : left_distance;
    Real distance = (front_distance * left_distance) / hypot(front_distance, left_distance);
    return distance < MAX_THRESHHOLD_WALL && distance > MIN_THRESHHOLD_WALL;
}

/****************************************/
/****************************************/

bool DistanceSensorsManager::ShouldAlighToLeft(bool right)
{
    return right ? GetRightDistance() > MAX_ALIGNING_WALL && GetRightDistance() < MAX_OUT_OF_RANGE
                 : GetLeftDistance() < MIN_ALIGNING_WALL && GetLeftDistance() > MIN_OUT_OF_RANGE;
}

/****************************************/
/****************************************/

bool DistanceSensorsManager::ShouldAlighToRight(bool right)
{
    return right ? GetRightDistance() < MIN_ALIGNING_WALL && GetRightDistance() > MIN_OUT_OF_RANGE
                 : GetLeftDistance() > MAX_ALIGNING_WALL && GetLeftDistance() < MAX_OUT_OF_RANGE;
}

/****************************************/
/****************************************/

bool DistanceSensorsManager::IsApproachingCorner(Direction direction)
{
    Real distance = FAR_DISTANCE;
    switch (direction)
    {
    case RIGHT_DIRECTION:
        distance = GetRightDistance();
        return distance < MAX_THRESHHOLD_CORNER && distance > MIN_THRESHHOLD_CORNER;

    case LEFT_DIRECTION:
        distance = GetLeftDistance();
        return distance < MAX_THRESHHOLD_CORNER && distance > MIN_THRESHHOLD_CORNER;

    default:
        return false;
    }
}

/****************************************/
/****************************************/
