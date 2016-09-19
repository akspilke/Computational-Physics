#include <iostream>
#include <armadillo>
#include <time.h>

using namespace arma;
using namespace std;
int main()

{
    int N = 10;                 // Defining the number of points we want for our approximation
    mat A = zeros<mat>(N,N);    // Defining the matrix A
    //mat A = randu<mat>(N,N);     //We also tried this with a random matrix, ie. not tridiagonal
    A.diag().fill(2);
    A.diag(1).fill(-1);
    A.diag(-1).fill(-1);

    vec b = randu<vec>(N);  // Defining b, really b tilde, h^2*f, rhs of equation
    A.print("A =");         // Printing A and b
    b.print("b =");

    clock_t start, end;     // Inserting the clock
    start = clock();        // Starting the clock

    // solve Ax = b
    vec x = solve(A,b);
    x.print("x =");     // print x

    // find LU decomp of A
    mat L, U;
    lu(L,U,A);

    L.print(" L = ");   // print L
    U.print(" U = ");   // print U

    // Check that A = LU
    (A-L*U).print("Test of LU decomposition");

    end = clock();  // Stops the clock

    // Prints CPU time
    printf("CPU cycles to execute Lu decomposition: %d\n", end-start);

    return 0;
}

