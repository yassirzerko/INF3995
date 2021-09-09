/* Include the controller definition */
#include "crazyflie_controlling.h"
/* Function definitions for XML parsing */
#include <argos3/core/utility/configuration/argos_configuration.h>
/* 2D vector definition */
#include <argos3/core/utility/math/vector2.h>
/* Logging */
#include <argos3/core/utility/logging/argos_log.h>

/****************************************/
/****************************************/

CCrazyflieControlling::CCrazyflieControlling() : m_pc_distance(NULL),
                                                 m_pc_propellers(NULL),
                                                 m_pc_RABA(NULL),
                                                 m_pc_RABS(NULL),
                                                 m_pc_pos(NULL),
                                                 m_pc_battery(std::make_unique<BatterySensor>()),
                                                 m_current_step(1),
                                                 m_heading(CRadians::ZERO),
                                                 m_state(NOT_READY),
                                                 m_commander(std::make_shared<Commander>()),
                                                 m_distance_manager(std::make_shared<DistanceSensorsManager>()),
                                                 m_return_to_base(std::make_unique<ReturnToBase>()),
                                                 m_exploration(std::make_unique<Exploration>()) {}

/****************************************/
/****************************************/

void CCrazyflieControlling::Init(TConfigurationNode &t_node)
{
   try
   {
      /*
       * Initialize sensors/actuators
       */
      m_pc_distance = GetSensor<CCI_CrazyflieDistanceScannerSensor>("crazyflie_distance_scanner");
      m_pc_propellers = GetActuator<CCI_QuadRotorPositionActuator>("quadrotor_position");
      /* Get pointers to devices */
      m_pc_RABA = GetActuator<CCI_RangeAndBearingActuator>("range_and_bearing");
      m_pc_RABS = GetSensor<CCI_RangeAndBearingSensor>("range_and_bearing");
      try {
         m_pc_pos = GetSensor<CCI_PositioningSensor>("positioning");
      } catch (CARGoSException &ex) {}
      try {
         m_pc_battery->Init(GetNode(t_node, "battery"));
      } catch (CARGoSException &ex) {}
   } catch (CARGoSException &ex) {
      THROW_ARGOSEXCEPTION_NESTED("Error initializing the crazyflie sensing controller for robot \"" << GetId() << "\"", ex);
   }
   m_commander->Init(m_pc_propellers, m_pc_pos, CRadians::ZERO);
   m_distance_manager->Init(m_pc_distance);
   m_exploration->Init(m_commander, m_distance_manager);
   m_return_to_base->Init(m_commander, m_distance_manager);
   SetLastPositions();
   SetLastPositions();
}

/****************************************/
/****************************************/

void CCrazyflieControlling::ControlStep()
{
   SetLastPositions();
   LogState();
   m_current_step++;
   switch (m_state)
   {
   case TAKING_OFF:
      m_pc_battery->UpdateAvailableCharge();
      m_commander->TakeOff(DRONE_HEIGHT);
      if (m_current_step > TIME_TO_TAKE_OFF)
         SetState(m_exploring_mode == SGBA ? EXPLORING : HOVERING);
      break;

   case EXPLORING:
      m_pc_battery->UpdateAvailableCharge();
      m_exploration->Execute(m_heading);
      if (GetBatteryLevel() < MIN_BATTERY_LEVEL)
         SetState(RETURNING_TO_BASE);
      break;

   case HOVERING:
      m_pc_battery->UpdateAvailableCharge();
      m_commander->SetImmediateOrientation(CRadians::PI / 10);
      break;

   case RETURNING_TO_BASE:
      m_pc_battery->UpdateAvailableCharge();
      if (m_return_to_base->Execute(m_heading))
      {
         SetState(LANDING);
      }
      break;

   case LANDING:
      m_pc_battery->UpdateAvailableCharge();
      m_commander->Land();
      if (m_current_step > TIME_TO_LAND)
      {
         SetState(GetBatteryLevel() < MIN_BATTERY_LEVEL ? NOT_READY : READY);
      }
      break;

   default:
      break;
   }
}

/****************************************/
/****************************************/

void CCrazyflieControlling::Reset()
{
}

/****************************************/
/****************************************/

void CCrazyflieControlling::SetLastPositions()
{
   m_last_positions.first = m_last_positions.second;
   m_last_positions.second = m_commander->GetCurrentPosition();
}

/****************************************/
/****************************************/

void CCrazyflieControlling::SetState(CrazyflieState state)
{
   if (m_state == state)
      return;
   m_state = state;
   m_commander->UpdateCurrentAngle();
   m_current_step = 0;
}

/****************************************/
/****************************************/

void CCrazyflieControlling::SetHeading(CRadians headingAngle)
{
   m_heading = headingAngle;
}

/****************************************/
/****************************************/

void CCrazyflieControlling::SetExploringMode(ExploringMode mode)
{
   m_exploring_mode = mode;
}

/****************************************/
/****************************************/

void CCrazyflieControlling::LogState()
{
   if (m_current_step != 0)
   {
      return;
   }
   switch (m_state)
   {
   case NOT_READY:
      std::cout << "Drone " << GetId() << " Is Not  Ready!" << std::endl;
      break;

   case READY:
      std::cout << "Drone " << GetId() << " Just Got Ready!" << std::endl;
      break;

   case TAKING_OFF:
      std::cout << "Drone " << GetId() << " is Taking Off!" << std::endl;
      break;

   case EXPLORING:
      std::cout << "Drone " << GetId() << " is Exploring Environement!" << std::endl;
      break;

   case RETURNING_TO_BASE:
      std::cout << "Drone " << GetId() << " is Returning to Base!" << std::endl;
      break;

   case LANDING:
      std::cout << "Drone " << GetId() << " is Landing!" << std::endl;
      break;

   default:
      break;
   }
}

/****************************************/
/****************************************/

CVector3 CCrazyflieControlling::GetPosition()
{
   return m_commander->GetCurrentPosition();
}

/****************************************/
/****************************************/

Real CCrazyflieControlling::GetOrientation()
{
   CRadians currentAngle;
   CVector3 vector(0.0f, 0.0f, 1.0f);
   m_pc_pos->GetReading().Orientation.ToAngleAxis(currentAngle, vector);
   return (currentAngle.UnsignedNormalize() / CRadians::TWO_PI) * 360.0f;
}

/****************************************/
/****************************************/

CVector3 CCrazyflieControlling::GetVelocity()
{
   Real velocityX = floor(Abs(m_last_positions.second.GetX() - m_last_positions.first.GetX()) / 0.1f * 100) / 100;
   Real velocityY = floor(Abs(m_last_positions.second.GetY() - m_last_positions.first.GetY()) / 0.1f * 100) / 100;
   Real velocityZ = floor(Abs(m_last_positions.second.GetZ() - m_last_positions.first.GetZ()) / 0.1f * 100) / 100;
   return CVector3(velocityX, velocityY, velocityZ);
}

/****************************************/
/****************************************/

Real CCrazyflieControlling::GetBatteryLevel()
{
   return floor(m_pc_battery->GetReading().AvailableCharge * 10000) / 100;
}

/****************************************/
/****************************************/

CrazyflieState CCrazyflieControlling::GetState()
{
   return m_state;
}

/****************************************/
/****************************************/

std::vector<Real> CCrazyflieControlling::GetDistanceSensorsData()
{
   std::vector<Real> data;
   // Read distance sensor
   CCI_CrazyflieDistanceScannerSensor::TReadingsMap sDistRead =
       m_pc_distance->GetReadingsMap();
   auto iterDistRead = sDistRead.begin();
   if (sDistRead.size() == N_DIRECTIONS)
   {
      data.push_back((iterDistRead++)->second);
      data.push_back((iterDistRead++)->second);
      data.push_back((iterDistRead++)->second);
      data.push_back((iterDistRead)->second);
   }
   else
   {
      data.push_back(FAR_DISTANCE);
      data.push_back(FAR_DISTANCE);
      data.push_back(FAR_DISTANCE);
      data.push_back(FAR_DISTANCE);
   }
   return data;
}

/*
 * This statement notifies ARGoS of the existence of the controller.
 * It binds the class passed as first argument to the string passed as
 * second argument.
 * The string is then usable in the XML configuration file to refer to
 * this controller.
 * When ARGoS reads that string in the XML file, it knows which controller
 * class to instantiate.
 * See also the XML configuration files for an example of how this is used.
 */
REGISTER_CONTROLLER(CCrazyflieControlling, "crazyflie_controlling_controller")
