#include <math.h>

#define PI 3.141592653589

/*
    This simulates two pendulums of equal mass and length.

    x[0], x[1]  : angle of each particle against the vertical
    x[2], x[3]  : angular velocity of each particle
*/

const int NUM_OF_VAR = 4;

void ode(double *dx, double *x, double t) {
    double cosine = cos(x[0]-x[1]);     // cos(a-b)
    double sine = sin(x[0]-x[1]);       // sin(a-b)

    dx[0] = x[2];
    dx[1] = x[3];
    dx[2] = -x[2]*x[2]*sine*cosine-x[3]*x[3]*sine+sin(x[1])*cosine-2*sin(x[0]);
    dx[3] = x[3]*x[3]*sine*cosine+2*x[2]*x[2]*sine+2*(sin(x[0])*cosine-2*sin(x[1]));
}

double X_INIT[] = {PI/4, PI/4, 0, 0};

const double T_INIT = 0;



const int NUM_OF_FREE = 0;

double FREE_VAL[] = {};

const double LOW_T = 0;
const double UPP_T = 0;

void low_bound(double *x_0, double *free_val, double t) {}


void upp_bound(double *err, double *x, double t) {}