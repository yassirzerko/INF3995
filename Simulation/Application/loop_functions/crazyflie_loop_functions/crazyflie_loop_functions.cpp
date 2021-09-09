#include "crazyflie_loop_functions.h"
#include <argos3/plugins/robots/crazyflie/simulator/crazyflie_entity.h>

/****************************************/
/****************************************/

CCrazyflieLoopFunctions::CCrazyflieLoopFunctions() : m_num_robots(0),
                                                     m_route(""),
                                                     m_current_step(0),
                                                     m_in_mission(false),
                                                     m_pcRNG(NULL) {}

/****************************************/
/****************************************/

CCrazyflieLoopFunctions::~CCrazyflieLoopFunctions()
{
}

/****************************************/
/****************************************/

void CCrazyflieLoopFunctions::Init(TConfigurationNode &t_tree)
{
    m_pcRNG = CRandom::CreateRNG("argos");
    argos::GetNodeAttribute(t_tree, "robots", m_num_robots);
    SetHeadingRobots();
    argos::GetNodeAttribute(t_tree, "route", m_route);
    EstablishConnection(m_route);
}

/****************************************/
/****************************************/

bool CCrazyflieLoopFunctions::EstablishConnection(const std::string &route)
{
    m_h.set_socket_open_listener([&](std::string const &nsp) {
        BindEvents();
        SetStateRobots(READY);
        m_h.socket("/argosSimulation")->emit("registerClient", sio::int_message::create(1));
    });
    m_h.set_close_listener([&](sio::client::close_reason const &reason) {
        SetStateRobots(NOT_READY);
    });
    m_h.set_fail_listener([&]() {
        m_h.close();
    });
    m_h.connect(route);
    return true;
}

/****************************************/
/****************************************/

void CCrazyflieLoopFunctions::BindEvents()
{
    m_h.socket(NAMESPACE)->on(COMMUNICATION_ROUTE, [&](sio::event &ev) {
        std::string message = ev.get_message()->get_map().at("runningAppData")->get_string();
        std::string readyCode = ev.get_message()->get_map().at("isRunningAppReady")->get_string();
        if (readyCode != "1")
        {
            // Find a way to exist safely
            std::cout << "Client is not connected!" << std::endl;
            return;
        }
        if (message != "None")
        {
            uint8_t command = std::stoi(message);
            switch (command)
            {
            case TAKE_OFF_COMMAND:
                std::cout << "Executing Take Off Command!" << std::endl;
                SetStateRobots(TAKING_OFF);
                break;

            case LAND_COMMAND:
                std::cout << "Executing Land Command!" << std::endl;
                SetStateRobots(LANDING);
                break;

            case RETURN_TO_BASE:
                std::cout << "Executing Return To Base Command!" << std::endl;
                SetStateRobots(RETURNING_TO_BASE);
                m_in_mission = false;
                break;

            case START_MISSION_COMMAND:
                std::cout << "Executing Start Mission Command!" << std::endl;
                SetStateRobots(TAKING_OFF, SGBA);
                m_in_mission = true;
                break;

            default:
                std::cout << "Command Not Found!" << std::endl;
                break;
            }
        }
    });
}

/****************************************/
/****************************************/

void CCrazyflieLoopFunctions::SetStateRobots(CrazyflieState state, ExploringMode mode)
{
    CSpace::TMapPerType &m_cCrazyflies = GetSpace().GetEntitiesByType("crazyflie");
    for (CSpace::TMapPerType::iterator it = m_cCrazyflies.begin();
         it != m_cCrazyflies.end();
         ++it)
    {
        CCrazyflieEntity &cCrazyflie = *any_cast<CCrazyflieEntity *>(it->second);
        CCrazyflieControlling &cController = dynamic_cast<CCrazyflieControlling &>(
            cCrazyflie.GetControllableEntity().GetController());
        cController.SetState(state);
        if (state == TAKING_OFF)
        {
            cController.SetExploringMode(mode);
        }
    }
}

/****************************************/
/****************************************/

void CCrazyflieLoopFunctions::SetHeadingRobots()
{
    CSpace::TMapPerType &m_cCrazyflies = GetSpace().GetEntitiesByType("crazyflie");
    UInt8 counter = 0;
    for (CSpace::TMapPerType::iterator it = m_cCrazyflies.begin();
         it != m_cCrazyflies.end();
         ++it)
    {
        CCrazyflieEntity &cCrazyflie = *any_cast<CCrazyflieEntity *>(it->second);
        CCrazyflieControlling &cController = dynamic_cast<CCrazyflieControlling &>(
            cCrazyflie.GetControllableEntity().GetController());
        cController.SetHeading((++counter) * CRadians::TWO_PI / (double)m_num_robots);
    }
}

/****************************************/
/****************************************/

void CCrazyflieLoopFunctions::SendDronesData()
{
    CSpace::TMapPerType &m_cCrazyflies = GetSpace().GetEntitiesByType("crazyflie");
    sio::message::ptr data = sio::object_message::create();
    sio::message::ptr drones = sio::object_message::create();
    sio::message::ptr swarm = sio::object_message::create();
    for (CSpace::TMapPerType::iterator it = m_cCrazyflies.begin();
         it != m_cCrazyflies.end();
         ++it)
    {
        CCrazyflieEntity &cCrazyflie = *any_cast<CCrazyflieEntity *>(it->second);
        CCrazyflieControlling &cController = dynamic_cast<CCrazyflieControlling &>(
            cCrazyflie.GetControllableEntity().GetController());
        drones->get_map().insert(std::pair<std::string, sio::message::ptr>(cController.GetId(), GetDronesData(
                                                                                                    cController.GetState(),
                                                                                                    cController.GetPosition(),
                                                                                                    cController.GetVelocity(),
                                                                                                    cController.GetBatteryLevel(),
                                                                                                    cController.GetOrientation(),
                                                                                                    cController.GetDistanceSensorsData())));
    }
    swarm->get_map().insert(std::pair<std::string, sio::message::ptr>("state", sio::bool_message::create(m_in_mission)));
    swarm->get_map().insert(std::pair<std::string, sio::message::ptr>("nDrones", sio::int_message::create(m_num_robots)));
    data->get_map().insert(std::pair<std::string, sio::message::ptr>("drones", drones));
    data->get_map().insert(std::pair<std::string, sio::message::ptr>("swarm", swarm));
    m_h.socket(NAMESPACE)->emit(COMMUNICATION_ROUTE, data);
}

/****************************************/
/****************************************/

sio::message::ptr CCrazyflieLoopFunctions::GetDronesData(
    const CrazyflieState droneState,
    const CVector3 &dronePosition,
    const CVector3 &droneVelocity,
    const Real &batteryLevel,
    const Real &orientation,
    const std::vector<Real> &sensorsData)
{
    sio::message::ptr data = sio::object_message::create();
    data->get_map().insert(std::pair<std::string, sio::message::ptr>("yaw", sio::double_message::create(orientation)));
    data->get_map().insert(std::pair<std::string, sio::message::ptr>("state", sio::int_message::create(droneState)));
    data->get_map().insert(std::pair<std::string, sio::message::ptr>("batteryLevel", sio::double_message::create(batteryLevel)));
    data->get_map().insert(std::pair<std::string, sio::message::ptr>("velocityZ", sio::double_message::create(droneVelocity.GetZ())));
    data->get_map().insert(std::pair<std::string, sio::message::ptr>("velocityY", sio::double_message::create(droneVelocity.GetY())));
    data->get_map().insert(std::pair<std::string, sio::message::ptr>("velocityX", sio::double_message::create(droneVelocity.GetX())));
    data->get_map().insert(std::pair<std::string, sio::message::ptr>("positionZ", sio::double_message::create(dronePosition.GetZ())));
    data->get_map().insert(std::pair<std::string, sio::message::ptr>("positionY", sio::double_message::create(dronePosition.GetY())));
    data->get_map().insert(std::pair<std::string, sio::message::ptr>("positionX", sio::double_message::create(dronePosition.GetX())));
    data->get_map().insert(std::pair<std::string, sio::message::ptr>("back", sio::double_message::create(sensorsData[0])));
    data->get_map().insert(std::pair<std::string, sio::message::ptr>("right", sio::double_message::create(sensorsData[1])));
    data->get_map().insert(std::pair<std::string, sio::message::ptr>("front", sio::double_message::create(sensorsData[2])));
    data->get_map().insert(std::pair<std::string, sio::message::ptr>("left", sio::double_message::create(sensorsData[3])));
    return data;
}

/****************************************/
/****************************************/

void CCrazyflieLoopFunctions::PostStep()
{
    m_current_step++;
    if (m_current_step % 10 == 0)
    {
        SendDronesData();
    }
}

/****************************************/
/****************************************/

REGISTER_LOOP_FUNCTIONS(CCrazyflieLoopFunctions, "crazyflie_loop_functions");
