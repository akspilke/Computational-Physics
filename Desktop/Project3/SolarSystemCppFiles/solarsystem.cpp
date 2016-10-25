#include "solarsystem.h"
#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>
using namespace std;

SolarSystem::SolarSystem() :
    m_kineticEnergy(0),
    m_potentialEnergy(0),
    m_l(0),
    m_Theta(0)
{
}
CelestialBody& SolarSystem::createCelestialBody(vec3 position, vec3 velocity, double mass, string name) {
    m_bodies.push_back( CelestialBody(position, velocity, mass, name) );
    return m_bodies.back(); // Return reference to the newest added celstial body
}
double dr = 0;

void SolarSystem::calculateForcesAndEnergy()
{
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;
    m_l = 0;
    m_angularMomentum.zeros();
    m_COM.zeros();
    m_Theta = 0;
    m_mimimumPositions.zeros();
    double dr = 0;

    for(CelestialBody &body : m_bodies) {
        // Reset forces on all bodies
        body.force.zeros();
    }
    for(int i=0; i<numberOfBodies(); i++) {
        CelestialBody &body1 = m_bodies[i];
        for(int j=i+1; j<numberOfBodies(); j++) {
            CelestialBody &body2 = m_bodies[j];
            vec3 deltaRVector = body1.position - body2.position;
            dr = deltaRVector.length();
            //body1.force += (-m_G*body1.mass*body2.mass*deltaRVector)/pow(dr,3);
            //body2.force -= (-m_G*body1.mass*body2.mass*deltaRVector)/pow(dr,3);

            // FOR GENERAL RELATIVITY GRAVITY THESE EQUATIONS FOR THE FORCE WERE USED
            m_l = (body2.position.cross(body2.velocity)).length();
            body1.force += ((-m_G*body1.mass*body2.mass*deltaRVector)/pow(dr,3))*(1 + (3*m_l*m_l)/(dr*dr*63197.8*63197.8));
            body2.force -= ((-m_G*body1.mass*body2.mass*deltaRVector)/pow(dr,3))*(1 + (3*m_l*m_l)/(dr*dr*63197.8*63197.8));

            // FOR TESTS OF CONSERVATION OF ENERGY AND ANGULAR MOMENTUM THESE EQUATIONS WERE USED
            //m_potentialEnergy = -(m_G*body1.mass*body2.mass)/dr;
            //m_angularMomentum += body1.mass*body1.velocity.lengthSquared()*dr;
            // TO FIND THE CENTRE OF MASS OF THE SYSTEM THIS EQUATION WAS USED
            //m_COM += (body1.mass*body1.position + body2.mass*body2.position)/(body1.mass + body2.mass);

            // FOR CALCULATIONS OF THE PERIHELION ANGLE OF MERCURY THIS EQUATION WAS INSERTED
            //m_Theta = atan((body2.position.y())/(body2.position.x()))*(3600.);
        }
        //m_kineticEnergy += 0.5*body1.mass*body1.velocity.lengthSquared();
    }
}
int SolarSystem::numberOfBodies() const
{
    return m_bodies.size();
}
double SolarSystem::totalEnergy() const
{
    return m_kineticEnergy + m_potentialEnergy;
}
double SolarSystem::potentialEnergy() const
{
    return m_potentialEnergy;
}
double SolarSystem::kineticEnergy() const
{
    return m_kineticEnergy;
}
void SolarSystem::writeToFile(string filename)
{
    if(!m_file.good()) {
        m_file.open(filename.c_str(), ofstream::out);
        if(!m_file.good()) {
            cout << "Error opening file " << filename << ". Aborting!" << endl;
            terminate();
        }
    }
    for(CelestialBody &body : m_bodies) {
        m_file << "1 " << body.position.x() << " " << body.position.y() << " " << body.position.z() << "\n";
    }
}
vec3 SolarSystem::angularMomentum() const
{
    return m_angularMomentum;
}
std::vector<CelestialBody> &SolarSystem::bodies()
{
    return m_bodies;
}
// CHANGING CENTRE OF MASS
void SolarSystem::removeTotalMomentum()
{
    vec3 P;
    P.zeros();

    for(int i=1; i<numberOfBodies(); i++) {
        CelestialBody &body = m_bodies[i];
        P += body.mass*body.velocity;
    }
    CelestialBody &sun = m_bodies[0];
    sun.velocity -= P;
}
