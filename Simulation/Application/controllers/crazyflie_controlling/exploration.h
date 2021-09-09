#ifndef EXPLORATION_H
#define EXPLORATION_H

/* Definitions for random number generation */
#include <argos3/core/utility/math/rng.h>
#include "wall_follower.h"

using namespace argos;

class Exploration : public WallFollower
{

public:
    Exploration();
    /* Execute The Wall Follower's Main Function */
    bool Execute(CRadians &heading_angle) override;
    /* Find a New Heading Angle To Detach From The Wall */
    bool SetNewHeading(CRadians &heading_angle) override;
    /* Keep Following The Wall Until It Ends */
    bool KeepFollowingWall(CRadians &heading_angle);

private:
    /* The random number generator */
    CRandom::CRNG *m_pc_RNG;
};

#endif
