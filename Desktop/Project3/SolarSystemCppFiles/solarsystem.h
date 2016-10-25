#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include "celestialbody.h"
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

class SolarSystem
{
public:
    SolarSystem();
    CelestialBody &createCelestialBody(vec3 position, vec3 velocity, double mass, std::string name);
    void calculateForcesAndEnergy();
    int numberOfBodies() const;

    double m_G = 4*M_PI*M_PI;
    double totalEnergy() const;         // const to make sure that this is not changed during the program
    double potentialEnergy() const;
    double kineticEnergy() const;
    void writeToFile(std::string filename);
    vec3 angularMomentum() const;
    vec3 COM() const;
    std::vector<CelestialBody> &bodies();
    void removeTotalMomentum();
private:
    std::vector<CelestialBody> m_bodies;// array of celestial bodies
    vec3 m_angularMomentum;             // Total angular momentum of system
    vec3 m_COM;
    vec3 m_mimimumPositions;
    std::ofstream m_file;
    double m_kineticEnergy;             // Setting properties of system
    double m_potentialEnergy;
    double m_l;
    double m_Theta;
};

// m_ member of system

#endif // SOLARSYSTEM_H
