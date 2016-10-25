#include "verlet.h"
#include "solarsystem.h"

Verlet::Verlet(double dt) :
    m_dt(dt)
{
}
void Verlet::integrateOneStep(SolarSystem &system)
{
    system.calculateForcesAndEnergy();
    for(CelestialBody &body : system.bodies()) {
        body.velocity += (m_dt/2)*(body.force / body.mass); //Calculate velocity at half step
        body.position += body.velocity*m_dt;
        // 5 flops
    }
    system.calculateForcesAndEnergy();
    for(CelestialBody &body : system.bodies()) {
        body.velocity += (m_dt/2)*(body.force / body.mass);
        // 3 flops
    }
}
