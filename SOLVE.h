#include <stdio.h>
#include "DEFS.h"

void solve_ivp(FILE *output, ODE ode, SOLVER solver, double *x_0, double t_0, double low_lim,
                double upp_lim, double err_or_steps, int num_of_pts);

void solve_bvp(FILE *output, ODE ode, BOUND low_bound, BOUND upp_bound, SOLVER solver,
                double low_lim, double upp_lim, double err_or_steps, int num_of_pts);