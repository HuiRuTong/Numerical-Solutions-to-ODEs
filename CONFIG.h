#ifndef CONFIG_H
#define CONFIG_H
/*
    I've tried to put all the variables you usually
    wouldn't change here as opposed to the .c file.

    Hopefully, you don't find yourself having the tweak
    these too often.
*/

/* MANDATORY: */
extern const int NUM_OF_VAR;
extern void ode(double *dx, double *x, double t);



/* IVP solver: */
extern double X_INIT[];
extern const double T_INIT;

// Initial step size for rk        
#define INIT_STEP 1e-6

// Minimum step size to prevent an extremely long rk
#define MIN_STEP 1e-12



/* BVP solver: */
extern const int NUM_OF_FREE;
extern double FREE_VAL[];
extern const double LOW_T;
extern const double UPP_T;
extern void low_bound(double *x_0, double *free_val, double t);
extern void upp_bound(double *err, double *x, double t);

// Step size for estimating the derivative of discrepancy
#define STEP_SIZE 1e-6

// Maximum allowable error for upper boundary
#define DISCREPANCY 1e-6

#endif