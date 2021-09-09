#ifndef RETURN_TO_BASE_H
#define RETURN_TO_BASE_H

#include "wall_follower.h"

const CVector2 BASE_STATION = CVector2(5.0f, 5.0f);

class ReturnToBase : public WallFollower
{

public:
    /* Class Contructor */
    ReturnToBase();
    /* Execute The Wall Follower's Main Function */
    bool Execute(CRadians &heading_angle) override;
    /* Find a New Heading Angle To Detach From The Wall */
    bool SetNewHeading(CRadians &heading_angle) override;
    /* Keep Following The Wall Until It Ends */
    bool KeepFollowingWall(CRadians &heading_angle);

private:
    /* Get The Distance Between The Drone and The Point target */
    Real GetDistanceFrom(CVector2 target);
    /* Return True If The Drone Is Able to Target The Point target */
    bool IsDirectionToTargetPossible(CVector2 target);
    /* Get The New Orientation To Get To The Point target */
    CRadians GetNewHeadingToTarget(CVector2 target);
};

#endif
