#ifndef BATTERY_SENSOR_H
#define BATTERY_SENSOR_H

/* Definitions for random number generation */
#include <argos3/core/utility/math/rng.h>
/* Definition of the crazyflie battery sensor */
#include <argos3/plugins/robots/generic/control_interface/ci_battery_sensor.h>

using namespace argos;

const Real STEP = 0.0005f;
const UInt8 ONE_MINUTE = 10;

class BatterySensor : public CCI_BatterySensor
{

public:
    /* Initialize The Sensor */
    void Init(TConfigurationNode &t_node)
    {
        UInt32 seed = 0;
        GetNodeAttribute(t_node, "seed", seed);
        m_pcRNG = CRandom::CreateRNG("argos");
        m_pcRNG->SetSeed(seed * rand());
        m_pcRNG->Reset();
        Real available_charge = m_pcRNG->Uniform(CRange<Real>(0.3f, 1.0f));
        m_sReading.AvailableCharge = available_charge;
        m_available_charge = available_charge;
        m_current_step = 0;
    };

    /* Update The Available Charge */
    void UpdateAvailableCharge()
    {
        m_current_step++;
        if (m_current_step % ONE_MINUTE)
        {
            m_sReading.AvailableCharge = m_available_charge;
            return;
        }
        m_available_charge -= STEP;
        m_sReading.AvailableCharge = m_available_charge;
    }

private:
    /* The Available Charge */
    Real m_available_charge;
    /* The Current Step */
    UInt64 m_current_step;
    /* The random number generator */
    CRandom::CRNG *m_pcRNG;
};

#endif
