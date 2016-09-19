#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <time.h>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char *argv[])

{
    // Setting where we want to save the output of this code
    ofstream outputFile;
    outputFile.open("uforN10.txt");
    outputFile << setiosflags(ios::showpoint | ios::uppercase);

    // Inserting a clock to measure the time of the algorithm
    clock_t start, end;

    // Defining the size of our matrix that we want to solve, ie. the number of points we want for our function
    int N = 10;
    // Defining arrays needed for our Thomas algorithm
    double *a = new double[N+2];    // Last element is N+1
    double *b = new double[N+2];
    double *c = new double[N+2];
    double *f = new double[N+2];
    double *u = new double[N+2];
    double *x = new double[N+2];
    double *uexact = new double[N+2];
    double *error = new double[N+2];

    // Defining the step length
    double h = 1.0/(N+1);

    // Defining the arrays we are using
    for (int i=0; i<N+2; i++){
        a[i]=2;                     // The diagonal of matrix A
        b[i]=-1;                    // The above diagonal of A
        c[i]=-1;                    // The below diagonal of A
        f[i]=h*h*100*exp(-10*i*h);    // This is really b tilde, fxh^2
        uexact[i]=1-(1-exp(-10))*i*h - exp(-10*i*h);  // The exact values of the function
    }
    // Starting the clock
    start = clock();

    // forward substitution
    for (int i=2; i<N+2; i++){    // starting at 2 because the first a we are changing is a2
        a[i] = a[i] - b[i-1]*c[i-1]/a[i-1];     // Using formulas produced in lectures to change the diagonal of A, from a to a tilde
        f[i] = f[i] - (f[i-1]*c[i-1])/a[i-1];   // Same for f -> changing to f tilde
        cout << a[i] << endl;
    }

    u[N]= f[N]/a[N];    // This gives values of u after the forward substitution

    // Backward substitution
    for (int i=N-1; i>=1; i--){
        u[i]=(f[i]-b[i]*u[i+1])/a[i];   // Redefining u to our final approximated value
        error[i] = log10(abs((u[i]-uexact[i])/uexact[i]));  // Calculating the relative error of our approximated u
        //cout << error[i] << endl;
    }

    // Reading our approximated u into an output file which will be plotted in Python
    for(int i = 0; i < N+2; i++){
        outputFile << setprecision(10) << setw(20) << u[i] << endl;
    }

    // Ending the the clock
    end = clock();

    // Printing the number of CPU cycles taken to run the algorithm
    printf("CPU cycles to execute integer multiplication operation: %d\n", end-start);

    // LU DECOMPOSITION, ARMADILLO'S BUILT IN ALGORITHM
    // Defining the matrix A, of total size N+2, and diagonals as above
    mat A =zeros<mat>(N+2, N+2);
    A.diag().fill(2);
    A.diag(1).fill(-1);
    A.diag(-1).fill(-1);

    // defining the vector b tilde, new name in order to not interfere with above code
    vec rhs = zeros<vec>(N+2);
    for (int i=0; i<N+2; i++){
        rhs(i)=h*h*100*exp(-10*i*h);    // b tilde, fxh^2
    }

    // Defining boundary conditions
    rhs(0) = 0;
    rhs(N+1) = 0;
    A(0,0) = 1;
    A(0,1) = 0;
    A(N+1,N+1) = 1;
    A(N+1,N) = 0;

    // Defining the lower triagonal matrix L and the upper triagonal matrix U
    mat L, U;
    lu(L,U,A);

    // Solving the problem with Lu decomposition
    vec y = solve(L, rhs);
    vec sol = solve(U, y);  // Gives the calculated u from this method

    // Finding the error of the LU decompostion and comparing it to the error of the Thomas method above
    double er = 0;
    for (int i = 0; i < N+2 ; i++) {
        er += fabs(sol(i)-u[i]);
    }
    // Printing the difference between the two errors
    cout << "error LU - thomas : " << er << endl;

    // This is not really necessary after we installed Armadillo, but ensures that all variables are deleted to free space on the computer for dynamic memory allocation
    delete [] a;
    delete [] b;
    delete [] c;
    delete [] x;
    delete [] u;
    delete [] f;
    delete [] uexact;
    delete [] error;
    // .. Continues with all the variables used in LU decomposition.

    // Returning 0 to inform the user that the code ended with success.
    return 0;
}
