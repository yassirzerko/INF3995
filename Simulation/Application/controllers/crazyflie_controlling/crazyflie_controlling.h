/*
 * The CrazyflieController Class
 */

#ifndef CRAZYFLIE_CONTROLLING_H
#define CRAZYFLIE_CONTROLLING_H

/*
 * Include some necessary headers.
 */
/* Definition of the CCI_Controller class. */
#include <argos3/core/control_interface/ci_controller.h>
/* Definition of the crazyflie distance sensor */
#include <argos3/plugins/robots/crazyflie/control_interface/ci_crazyflie_distance_scanner_sensor.h>
/* Definition of the crazyflie position actuator */
#include <argos3/plugins/robots/generic/control_interface/ci_quadrotor_position_actuator.h>
/* Definition of the crazyflie position sensor */
#include <argos3/plugins/robots/generic/control_interface/ci_positioning_sensor.h>
/* Definition of the crazyflie range and bearing actuator */
#include <argos3/plugins/robots/generic/control_interface/ci_range_and_bearing_actuator.h>
/* Definition of the crazyflie range and bearing sensor */
#include <argos3/plugins/robots/generic/control_interface/ci_range_and_bearing_sensor.h>
/* Definition of the crazyflie battery sensor */
#include "battery_sensor.h"
/* Definition of the ReturnToBase class*/
#include "return_to_base.h"
/* Definition of the Exploration class*/
#include "exploration.h"

/*
 * All the ARGoS stuff in the 'argos' namespace.
 * With this statement, you save typing argos:: every time.
 */
using namespace argos;

enum CrazyflieState
{
   NOT_READY = 0,
   READY,
   TAKING_OFF,
   LANDING,
   HOVERING,
   EXPLORING,
   RETURNING_TO_BASE
};

enum ExploringMode
{
   SGBA = 0,
   HOVER
};

const Real VELOCITY = 0.08f;
const UInt64 DELAY_SPEED_ZERO = 10000;
const UInt32 TIME_TO_TAKE_OFF = 30;
const UInt32 TIME_TO_LAND = 50;
const Real DRONE_HEIGHT = 1.5f;
const Real MIN_BATTERY_LEVEL = 30.0f;

/*
 * A controller is simply an implementation of the CCI_Controller class.
 */
class CCrazyflieControlling : public CCI_Controller
{

public:
   /* Class constructor. */
   CCrazyflieControlling();
   /* Class destructor. */
   virtual ~CCrazyflieControlling() {}
   /*
    * This function initializes the controller.
    * The 't_node' variable points to the <parameters> section in the XML
    * file in the <controllers><footbot_foraging_controller> section.
    */
   virtual void Init(TConfigurationNode &t_node);
   /*
    * This function is called once every time step.
    * The length of the time step is set in the XML file.
    */
   virtual void ControlStep();
   /*
    * This function resets the controller to its state right after the
    * Init().
    * It is called when you press the reset button in the GUI.
    */
   virtual void Reset();
   /*
    * Called to cleanup what done by Init() when the experiment finishes.
    * In this example controller there is no need for clean anything up,
    * so the function could have been omitted. It's here just for
    * completeness.
    */
   virtual void Destroy() {}
   /* This function returns true if the drone is near the position "position" */
   void SetLastPositions();
   /* This function sets the attribute m_state of the controller to the valuer "state" */
   void SetState(CrazyflieState state);
   /* This function sets the attribute m_heading of the controller to the valuer "hadingAngle" */
   void SetHeading(CRadians headingAngle);
   /* This function sets the attribute m_exploring_mode of the attribute m_exploration to "mode" */
   void SetExploringMode(ExploringMode mode);
   /* This function logs the attribute m_state of the controller when it's changed */
   void LogState();
   /* This function returns the controller's position */
   CVector3 GetPosition();
   /* This function returns the controller's yaw */
   Real GetOrientation();
   /* This function returns the controller's velocity */
   CVector3 GetVelocity();
   /* This function returns the controller's battery level */
   Real GetBatteryLevel();
   /* This function returns the controller's battery level */
   CrazyflieState GetState();
   /* This function returns the controller's distance sensors data */
   std::vector<Real> GetDistanceSensorsData();

private:
   /* Pointer to the crazyflie distance sensor */
   CCI_CrazyflieDistanceScannerSensor *m_pc_distance;
   /* Pointer to the position actuator */
   CCI_QuadRotorPositionActuator *m_pc_propellers;
   /* Pointer to the range and bearing actuator */
   CCI_RangeAndBearingActuator *m_pc_RABA;
   /* Pointer to the range and bearing sensor */
   CCI_RangeAndBearingSensor *m_pc_RABS;
   /* Pointer to the positioning sensor */
   CCI_PositioningSensor *m_pc_pos;
   /* Pointer to the battery sensor */
   std::unique_ptr<BatterySensor> m_pc_battery;
   /* The two last position of the drone */
   std::pair<CVector3, CVector3> m_last_positions;
   /* Steps counter */
   uint m_current_step;
   /* Current state */
   CrazyflieState m_state;
   /* Heading angle */
   CRadians m_heading;
   /* Return To Base component */
   std::unique_ptr<ReturnToBase> m_return_to_base;
   /* Exploration component */
   std::unique_ptr<Exploration> m_exploration;
   /* The Drone Commander */
   std::shared_ptr<Commander> m_commander;
   /* The Distance Sensors Manager */
   std::shared_ptr<DistanceSensorsManager> m_distance_manager;
   /* Exploring Mode */
   ExploringMode m_exploring_mode;
};

#endif
