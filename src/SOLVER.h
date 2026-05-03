#ifndef SOLVER_H
#define SOLVER_H
#include "DEFS.h"

/* IVP solver: */
// t_0 stays as a parameter since, the bvp solver requires a different t_init
double *euler(ODE ode, double *x_0, double t_0, double t, double steps);

double *rk23(ODE ode, double *x_0, double t_0, double t, double err_tol);
double *rk45(ODE ode, double *x_0, double t_0, double t, double err_tol);

/* IVP solver: */
double *shoot(ODE ode, BOUND low_bound, BOUND upp_bound, SOLVER solver, double err_or_steps);

#endif