/*
 * This example shows how to define custom distributions to place the robots.
 */

#include <argos3/core/simulator/loop_functions.h>
#include <controllers/crazyflie_controlling/crazyflie_controlling.h>
#include "sio_client.h"

const uint8_t TAKE_OFF_COMMAND = 0;
const uint8_t LAND_COMMAND = 1;
const uint8_t START_MISSION_COMMAND = 2;
const uint8_t RETURN_TO_BASE = 3;

const std::string NAMESPACE = "/argosSimulation";
const std::string COMMUNICATION_ROUTE = "communication";

using namespace argos;

class CCrazyflieLoopFunctions : public CLoopFunctions
{

public:
   /* Class constructor */
   CCrazyflieLoopFunctions();
   /* Class destructor */
   virtual ~CCrazyflieLoopFunctions();
   /* Init function */
   virtual void Init(TConfigurationNode &t_tree);
   /* Executed after every step of the experiment */
   virtual void PostStep();
   /* Bind socketio events */
   void BindEvents();
   /* Establish connection with the server */
   bool EstablishConnection(const std::string &route);
   /* Set the state and the exploring mode of the drones to state and mode */
   void SetStateRobots(CrazyflieState state, ExploringMode mode = HOVER);
   /* Set the initial heading angle of the drones */
   void SetHeadingRobots();
   /* Send the drones data to the server */
   void SendDronesData();
   /* Get the drones data from the crazyflie controllers */
   sio::message::ptr GetDronesData(
       const CrazyflieState droneState,
       const CVector3 &dronePosition,
       const CVector3 &droneVelocity,
       const Real &batteryLevel,
       const Real &orientation,
       const std::vector<Real> &sensorsData);

private:
   argos::UInt8 m_num_robots;
   argos::CSet<CVector3> m_pos_robots;
   std::string m_route;
   argos::UInt32 m_current_step;
   sio::client m_h;
   CRandom::CRNG *m_pcRNG;
   bool m_in_mission;
};
