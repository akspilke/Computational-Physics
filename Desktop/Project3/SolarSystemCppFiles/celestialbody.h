#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H
#include <string>

#include "vec3.h"

class CelestialBody
{
public:
    vec3 position;
    vec3 velocity;
    vec3 force;
    double mass;
    std::string name;

    // Two constructors:
    CelestialBody(vec3 position, vec3 velocity, double mass, std::string name_);
    CelestialBody(double x, double y, double z, double vx, double vy, double vz, double mass, std::string name_);
    void resetForce();
};

#endif // CELESTIALBODY_H
