#include <math.h>
#include "DEFS.h"
#include "CONFIG.h"

double X_INIT[NUM_OF_VAR] = {-2.0, 3.368132};

void ode(double *dx, double *x, double t) {
    /*
        This function defines a system of ODEs.

        dx  : vector representing the first derivative of x at t
        x   : vector representing the values of x at t
        t   : do you really need a descriptor for this?

        Below is an example of the system:
            x_1' = 2(x_2) + 3t
            x_2' = e^(-4t)
    */
    dx[0] = 2*x[1] + 3*t;
    dx[1] = exp(-4*t);
}



double FREE_VAL[NUM_OF_FREE] = {2};

void low_bound(double *x_0, double *free_val, double t) {
    /*
        This function defines the lower boundary of a bvp

        x_0         : vector representing the values of x at the lower boundary
        free_val    : vector representing guesses for the unknown initial values of x
        t           : value of t at lower boundary i.e. low_t

        Note that you have to manually assign each free_val[j] to their respective x_0[i].
        Below is an example of the bounds:
            x_2(low_t) = x_1(low_t) - 3
    */
   x_0[0] = free_val[0];
   x_0[1] = x_0[0] - 3;
}

void upp_bound(double *err, double *x, double t) {
    /*
        This function defines the upper boundary of a bvp

        err         : vector representing the difference between the upper boundaries and x
        x           : vector representing the estimated values of x at the upper boundary
        t           : value of t at lower boundary i.e. low_t

        Below is an example of the bounds:
            x_1(upp_t) = -2
            -> x_1(upp_t) + 2 = 0
    */
   err[0] = x[0] + 2;
}