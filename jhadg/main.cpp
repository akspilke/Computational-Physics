#include <iostream>
#include "vec3.h"

using namespace std;

int main(int argc, char *argv[])
{
    vec3 a;
    vec3 b;
    a(0) += 2;
    b(1) = 5;
    b -= a; // b = b - a, subtracting two vectors
    b += a; // b = b + a, adding two vectors

    cout << b[0] << endl;
    cout << a[0] << endl;

    // vec3 myVector;
    // cout << myVector(0) << endl;
    // myVector[2]
    // myVector(0) += 2;
    // cout << myVector(0) << endl;
    // cout << myVector.lengthSquared() << endl;
    // cout << myVector.length() << endl;

    return 0;
}
