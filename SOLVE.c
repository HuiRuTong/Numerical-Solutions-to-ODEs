#include <stdlib.h>
#include <stdio.h>
#include "DEFS.h"
#include "CONFIG.h"
#include "SOLVER.h"

static void propagate(double **x_0, double **x, double *t_0, double t,
                        FILE *output, ODE ode, SOLVER solver, double *x_init,
                        double t_init, double err_or_steps) {
    // Updates initial pt to be closer to the next pt
    // Reduces computation time for rk; has no effect on Euler
    *x = solver(ode, *x_0, *t_0, t, err_or_steps);
    if (*x_0 != x_init) {
        free(*x_0);
    }
    
    fprintf(output, "% lf\t", t);
    for (int i = 0; i < NUM_OF_VAR; i++) {
        fprintf(output, "% lf\t", (*x)[i]);
    }
    fprintf(output, "\n");
    
    *x_0 = *x;
    *t_0 = t;
}

void solve_ivp(FILE *output, ODE ode, SOLVER solver, double *x_init, double t_init,
                double low_lim, double upp_lim, double err_or_steps, int num_of_pts) {
    double dt = (upp_lim - low_lim) / (double) num_of_pts;
    double *x_0 = x_init;
    double *x;
    double t_0 = t_init;
    double t = t_init;
    
    // You should make sure that t_init is included inside of estimated points
    while (t >= low_lim) {
        propagate(&x_0, &x, &t_0, t, output, ode, solver, x_init, t_init, err_or_steps);
        t -= dt;
    }
    free(x);

    x_0 = x_init;
    t_0 = t_init;
    t = t_init;

    if (t != upp_lim) {     // I have no idea why you'd ever have t_init be the largest point but eh
        while (t < upp_lim) {
            t += dt;
            propagate(&x_0, &x, &t_0, t, output, ode, solver, x_init, t_init, err_or_steps);
        }
        free(x);
    }
}

void solve_bvp(FILE *output, ODE ode, BOUND low_bound, BOUND upp_bound, SOLVER solver,
                double low_lim, double upp_lim, double err_or_step, int num_of_pts) {
    double *x_init = shoot(ode, low_bound, upp_bound, solver, err_or_step);
    double t_init = LOW_T;

    double dt = (upp_lim - low_lim) / (double) num_of_pts;
    double *x_0 = x_init;
    double *x;
    double t_0 = t_init;
    double t = t_init;

    solve_ivp(output, ode, solver, x_init, t_init, low_lim, upp_lim, err_or_step, num_of_pts);
    free(x_init);
}