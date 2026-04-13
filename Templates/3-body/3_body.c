#include <math.h>

/*
    This simulates a classic 2D three-body problem. At the start of
    the simulation, the particles are moving clockwise.

    x[0], x[4], x[8]    : x-coordinate of each particle
    x[1], x[5], x[9]    : y-coordinate of each particle
    x[2], x[6], x[10]   : x-velocity of each particle
    x[3], x[9], x[11]   : y-velocity of each particle
*/

const int NUM_OF_VAR = 12;

void ode(double *dx, double *x, double t) {
    double r12 = pow((x[0]-x[4])*(x[0]-x[4])+(x[1]-x[5])*(x[1]-x[5]), 0.5);
    double r23 = pow((x[4]-x[8])*(x[4]-x[8])+(x[5]-x[9])*(x[5]-x[9]), 0.5);
    double r13 = pow((x[0]-x[8])*(x[0]-x[8])+(x[1]-x[9])*(x[1]-x[9]), 0.5);     // distances between each particle

    dx[0] = x[2];
    dx[1] = x[3];
    dx[2] = (x[4] - x[0]) / (r12*r12*r12) + (x[8] - x[0]) / (r13*r13*r13);
    dx[3] = (x[5] - x[1]) / (r12*r12*r12) + (x[9] - x[1]) / (r13*r13*r13);
    dx[4] = x[6];
    dx[5] = x[7];
    dx[6] = (x[0] - x[4]) / (r12*r12*r12) + (x[8] - x[4]) / (r23*r23*r23);
    dx[7] = (x[1] - x[5]) / (r12*r12*r12) + (x[9] - x[5]) / (r23*r23*r23);
    dx[8] = x[10];
    dx[9] = x[11];
    dx[10] = (x[0] - x[8]) / (r13*r13*r13) + (x[4] - x[8]) / (r23*r23*r23);
    dx[11] = (x[1] - x[9]) / (r13*r13*r13) + (x[5] - x[9]) / (r23*r23*r23);
}

double X_INIT[] = {-1, 0, 0, 0.5, 1, 0, 0, -0.5, 0, 1, 0, 0.5, 0};

const double T_INIT = 0;



const int NUM_OF_FREE = 0;

double FREE_VAL[] = {};

const double LOW_T = 0;
const double UPP_T = 0;

void low_bound(double *x_0, double *free_val, double t) {}


void upp_bound(double *err, double *x, double t) {}