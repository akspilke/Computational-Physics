#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include "time.h"
using namespace std;

int main(int argc, char *argv[])
{
    double massSun = 1.98855e30; // kg
    double massEarth = 5.97237e24; // kg
    double radiusEarthSun = 1.496e11; // m
    double G = 6.674*pow(10, -11); // N⋅m2/kg2.

    double ForceNewtonGravity = (G*massSun*massEarth)/(radiusEarthSun*radiusEarthSun);




    return 0;
}
