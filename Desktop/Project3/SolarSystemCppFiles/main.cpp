#include <iostream>
#include <cmath>
#include <string>
#include "solarsystem.h"
#include "verlet.h" // change when running with Euler method
#include <iterator>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <time.h>
#include <ctime>
using namespace std;

int main(int numArguments, char **arguments)
{
    double tfinal = 1.0;    // set final time in years
    double dt = 1e-8;       // set size of timesteps
    long int numTimesteps = tfinal/dt;
    if(numArguments >= 2) numTimesteps = atoi(arguments[1]);

    SolarSystem solarSystem;

    CelestialBody &sun = solarSystem.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0, string("Sun"));
    // first vec3 is position, 2nd velocity, 3rd mass, 4th name

    // MASS OF PLANETS
    //double massJupiter = (1.9e27)/(2e30); //solar units
    //double massMars = (6.6e23)/(2e30); //solar units
    //double massVenus = (4.9e24)/(2e30); //solar units
    //double massSaturn = (5.5e26)/(2e30); //solar units
    //double massMercury = (2.4e23)/(2e30); //solar units
    //double massUranus = (8.8e25)/(2e30); //solar units
    //double massNeptun = (1.03e26)/(2e30); //solar units
    //double massPluto = (1.31e22)/(2e30); //solar units

    // EARTH CIRCULAR AND NASA
    //solarSystem.createCelestialBody( vec3(1, 0, 0), vec3(0, 2*M_PI, 0), 3e-6,  string("Earth") );
    //solarSystem.createCelestialBody( vec3(9.356619245372438E-01,  3.583403516829250E-01, -1.773262707105873E-04), (365)*vec3(-6.405361360564236E-03, 1.601367683562308E-02, 1.363153389446707E-07), 3e-6,  string("Earth"));

    // JUPITER CIRCULAR ORBIT
    //double velJupiter = (2*M_PI*distanceJupiter)/(11.862615); //AU/year
    //double distanceJupiter = 5.20; //AU
    //solarSystem.createCelestialBody( vec3(distanceJupiter, 0, 0), vec3(0, velJupiter, 0), massJupiter, string("Jupiter") );

    // MERCURY PERIHELION
    //solarSystem.createCelestialBody( vec3(0.3075,  0,  0), vec3( 0, 12.44, 0), massMercury, string("Mercury") );

    // ALL BODIES FROM NASA START TIME 14.OCTOBER 2016 00.00.00
    //solarSystem.createCelestialBody( vec3(-5.429091121847574E+00, -4.464121857033960E-01,  1.232706724471818E-01), 365*vec3(5.310921442239308E-04, -7.163232763813381E-03,  1.792277878205211E-05), massJupiter, string("Jupiter") );
    //solarSystem.createCelestialBody( vec3(1.153835515595857E+00, -7.631393683685221E-01, -4.445323059570280E-02), 365*vec3(8.290101223222136E-03,  1.285064506000931E-02,  6.568487018774290E-05), massMars, string("Mars") );
    //solarSystem.createCelestialBody( vec3(1.814959969646973E-01, -7.018747180931129E-01, -2.009798680125879E-02), 365*vec3(1.947420769434422E-02,  4.885314858116717E-03, -1.056966494215987E-03), massVenus, string("Venus") );
    //solarSystem.createCelestialBody( vec3(-2.272178928493247E+00, -9.773535746042706E+00,  2.603649145748581E-01), 365*vec3(5.127458852019526E-03, -1.281135103943108E-03, -1.815744049938347E-04), massSaturn, string("Saturn") );
    //solarSystem.createCelestialBody( vec3(-3.448088926082000E-01,  1.060250803722253E-01,  4.018631514146201E-02), 365*vec3(-1.377317016029842E-02, -2.577724446766713E-02, -8.434331741010699E-04), massMercury, string("Mercury") );
    //solarSystem.createCelestialBody( vec3(1.846474430744711E+01,  7.557968549777230E+00, -2.111440417889109E-01), 365*vec3(-1.518690330813693E-03, 3.456622065519562E-03,  3.238173155986076E-05), massUranus, string("Uranus") );
    //solarSystem.createCelestialBody( vec3(2.825991344979922E+01, -9.925274968694582E+00, -4.468864440491235E-01), 365*vec3(1.018892127682802E-03, 2.980370221614675E-03, -8.457448803019877E-05), massNeptun, string("Neptun") );
    //solarSystem.createCelestialBody( vec3(9.420766235048019E+00, -3.181847836470213E+01,  6.797405414511198E-01), 365*vec3(3.082778705023476E-03, 2.516987371233560E-04, -9.111893058927559E-04), massPluto, string("Pluto") );

    // To get a list (a reference, not copy) of all the bodies in the solar system, we use the .bodies() function
    //vector<CelestialBody> &bodies = solarSystem.bodies();

    // Inserting a clock to measure the time of the algorithm
    //const clock_t begin_time = clock();

    // TIME INTEGRATION LOOP FOR EVERYTHING EXCEPT PERIHELION
    //for(int i = 0; i<bodies.size(); i++) {
    //    CelestialBody &body = bodies[i]; // Reference to this body
    //    cout << "The position of " << body.name << " is " << body.position << " with velocity " << body.velocity << " and mass " << body.mass << endl;
    //}
    // Time integration
    // double dt = 1e-3;
    //Verlet integrator(dt);
    //for(int timestep=0; timestep<numTimesteps; timestep++) {
    //    integrator.integrateOneStep(solarSystem);
    //    solarSystem.writeToFile("PerihelionMercury.txt");
    //}
    //cout << "I just created my first solar system that has " << solarSystem.bodies().size() << " objects." << endl;
    //cout << "Creating this Solar System with " << numTimesteps <<" timesteps took " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << " seconds." << endl;

    // PERIHELION OF MERCURY
    CelestialBody &mercury = solarSystem.createCelestialBody(vec3(0.3075, 0, 0), vec3(0, 12.44, 0), 1.65e-7, string("Mercury") );

    ofstream myfile;
    string filename = "PerihelionMercury10YR10.txt";
    if(!myfile.is_open()) {
        myfile.open(filename.c_str(), ios_base::out);
    }
    vector<CelestialBody> &bodies = solarSystem.bodies();

    double rOld = 0;
    double rPrev = 0;
    double r = 0;
    double thetaPrev = 0;

    Verlet integrator(dt);
    for(long int time = 0; time < numTimesteps; time++){
        integrator.integrateOneStep(solarSystem);

        double x = bodies[1].position.x() - bodies[0].position.x();
        double y = bodies[1].position.y() - bodies[0].position.y();
        double thetaCurrent = atan2(y, x);
        double rCurrent = (bodies[1].position - bodies[0].position).length();

        if(rCurrent > rPrev && rPrev < rOld){
            myfile << thetaPrev << endl;
            myfile << time << endl;
        }
        rOld = rPrev;
        rPrev = rCurrent;
        thetaPrev = thetaCurrent;
     }
     cout << thetaPrev << endl;

    return 0;
}

