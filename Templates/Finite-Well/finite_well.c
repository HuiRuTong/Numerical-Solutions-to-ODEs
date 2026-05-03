#include <math.h>

/*
    This solves for the bound states of the quantum finite
    square well (when E < V).

    x[0], x[2]  : wavefunction outside and inside the well respectively
    x[1], x[3]  : derivative of x[0] and x[2] respectively
*/

/* MANDATORY: */
const int NUM_OF_VAR = 4;

void ode(double *dx, double *x, double t) {
    dx[0] = x[1];
    dx[1] = -2*(5+0.5)*x[0];
    dx[2] = x[3];
    dx[3] = -2*x[2];
}


/* IVP: */
double X_INIT[] = {};

const double T_INIT = 0;


/* BVP: */
const int NUM_OF_FREE = 2;

double FREE_VAL[] = {-1e-2, 1e-2};

const double LOW_T = -0.5;
const double UPP_T = 0.5;

void low_bound(double *x_0, double *free_val, double t) {
    x_0[2] = free_val[0];
    x_0[3] = free_val[1];

    x_0[0] = x_0[2];
    x_0[1] = x_0[3];
}
void upp_bound(double *err, double *x, double t) {
    err[0] = x[2] - x[0];
    err[1] = x[3] - x[1];
}