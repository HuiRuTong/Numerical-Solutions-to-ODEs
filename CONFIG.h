#ifndef CONFIG_H
#define CONFIG_H
/*
    I've tried to put all the variables you usually
    wouldn't change here as opposed to making them
    runtime arguments.

    Hopefully, you don't find yourself having the tweak
    these too often.
*/

/* MANDATORY: */
// total number of variables in an ode
#define NUM_OF_VAR 2

// system of ode; see CONFIg.c for more details
extern void ode(double *dx, double *x, double t);



/* IVP solver: */
// vector representing initial values
extern double X_INIT[NUM_OF_VAR];

// initial value of t
#define T_INIT 0

// initial step size for rk        
#define INIT_STEP 1e-6



/* BVP solver: */
// number of free variables in a bvp
#define NUM_OF_FREE 1

// vector representing guesses for unknown initial values
extern double FREE_VAL[NUM_OF_FREE];

// value of t at the lower and upper boundaries
#define LOW_T 1
#define UPP_T 0

// boundaries; see CONFIg.c for more details
extern void low_bound(double *x_0, double *free_val, double t);
extern void upp_bound(double *err, double *x, double t);

// Step size for estimating the derivative of discrepancy
#define STEP_SIZE 1e-6

// Maximum allowable error for upper boundary
#define DISCREPANCY 1e-4

#endif