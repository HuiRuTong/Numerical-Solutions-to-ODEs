#include <math.h>

/*
    This is an example of what your config files should look like.
    If you're solving an IVP, you should leave the BVP section untouched,
    and vice versa. Because C is annoying, you can't delete the unneeded
    variables.
*/

/* MANDATORY: */
// total number of variables in an ode
const int NUM_OF_VAR = 2;

// system of ode; see CONFIg.c for more details
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


/* IVP: */
// vector representing initial values
double X_INIT[] = {-2.0, 3.368132};     // MAKE SURE you enter the right amount of elements 

// initial value of t
const double T_INIT = 0;


/* BVP: */
// number of free variables in a bvp
const int NUM_OF_FREE = 1;

// vector representing guesses for unknown initial values
double FREE_VAL[] = {2};

// value of t at the lower and upper boundaries
// UPP_T need not be > LOW_T; in fact, you should pick UPP_T such that NUM_OF_FREE is minimised
const double LOW_T = 1;
const double UPP_T = 0;

// boundaries
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