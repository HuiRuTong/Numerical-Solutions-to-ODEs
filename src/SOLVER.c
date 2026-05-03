#include <stdlib.h>
#include <math.h>
#include "DEFS.h"
#include "CONFIG.h"

double *euler(ODE ode, double *x_0, double t_0, double t, double steps) {
    /*
        ode             : function defining system of ODEs
        x_0             : initial values of x at t_0 i.e. x(t_0)
        t_0             : initial value of t
        t               : value of t where x is to be estimated
        steps           : the number of steps taken from t_0 to t
    */
    // For compatibility reasons, I've kept steps as a double
    double h = (t - t_0) / (long int) steps;            // step size used in each iteration
    double *x = malloc(sizeof(double) * NUM_OF_VAR);    // estimated x(t)
    for (int i = 0; i < NUM_OF_VAR; i++) {
        x[i] = x_0[i];
    }

    if (t == t_0) {return x;}

    double *fx = malloc(sizeof(double) * NUM_OF_VAR);

    for (int i = 0; i < steps; i++) {
        ode(fx, x, t_0);

        /*
            Every single time I'm forced to write another for
            bc C doesn't support vector addition, I lose a bit
            of my will to live
        */
        for (int i = 0; i < NUM_OF_VAR; i++) {
            x[i] += fx[i] * h;
        }
        t_0 += h;
    }

    free(fx);

    return x;
}

double *rk23(ODE ode, double *x_0, double t_0, double t, double err_tol) {
    /*
        ode             : function defining system of ODEs
        x_0             : initial values of x at t_0 i.e. x(t_0)
        t_0             : initial value of t
        t               : value of t where x is to be estimated
        err_tol         : maximum allowable error for each rk step
    */
    double *x = malloc(sizeof(double) * NUM_OF_VAR);
    double *x_temp = malloc(sizeof(double) * NUM_OF_VAR);   // stores operations on x_0 since
                                                            // I can't alter x between each k
    double h = 0;
    double err = 0;

    for (int i = 0; i < NUM_OF_VAR; i++) {
        x[i] = x_0[i];
    }

    /*
        The initial step size was supposed to be an argument,
        but for compatibility with euler >:(, I've decided to
        just make it an arbitrary constant
    */
    if (t == t_0) {
        return x;
    } else if (t < t_0) {
        h = -INIT_STEP;
    } else {
        h = INIT_STEP;
    }

    double *k_1 = malloc(sizeof(double) * NUM_OF_VAR);
    double *k_2 = malloc(sizeof(double) * NUM_OF_VAR);
    double *k_3 = malloc(sizeof(double) * NUM_OF_VAR);
    double *k_4 = malloc(sizeof(double) * NUM_OF_VAR);
    
    while ((h < 0 && t < t_0) || (h > 0 && t > t_0)) {
        ode(k_1, x, t_0);
        for (int i = 0; i < NUM_OF_VAR; i++) {
            x_temp[i] = x[i] + 0.5 * k_1[i] * h;
        }
        ode(k_2, x_temp, t_0 + 0.5*h);
        for (int i = 0; i < NUM_OF_VAR; i++) {
            x_temp[i] = x[i] + 0.75 * k_2[i] * h;
        }
        ode(k_3, x_temp, t_0 + 0.75*h);
        for (int i = 0; i < NUM_OF_VAR; i++) {
            x_temp[i] = x[i] + (2*k_1[i] + 3*k_2[i] + 4*k_3[i]) * h / 9.0;
        }
        ode(k_4, x_temp, t_0 + h);

        for (int i = 0; i < NUM_OF_VAR; i++) {
            err += (-5*k_1[i] + 6*k_2[i] + 8*k_3[i] - 9*k_4[i]) *
                   (-5*k_1[i] + 6*k_2[i] + 8*k_3[i] - 9*k_4[i]) * h*h / 5184.0;
        }
        err = pow(err, 0.5);

        // After much frustration, I've decided to hardcode a stop for this thing
        // Any negligible h means the loop has practically stopped anyway
        if (err <= err_tol || fabs(h) < MIN_STEP) {
            for (int i = 0; i < NUM_OF_VAR; i++) {
                x[i] += (2*k_1[i] + 3*k_2[i] + 4*k_3[i] ) * h / 9.0;
            }
            t_0 += h;
        } else {
            h *= 0.8*pow(err_tol / err, 1/3.0);
        }

        err = 0;
    }

    free(x_temp);
    free(k_1);
    free(k_2);
    free(k_3);
    free(k_4);

    return x;
}

double *rk45(ODE ode, double *x_0, double t_0, double t, double err_tol) {
    /*
        ode             : function defining system of ODEs
        x_0             : initial values of x at t_0 i.e. x(t_0)
        t_0             : initial value of t
        t               : value of t where x is to be estimated
        err_tol         : maximum allowable error for each rk step
    */
    double *x = malloc(sizeof(double) * NUM_OF_VAR);
    double *x_temp = malloc(sizeof(double) * NUM_OF_VAR);
    double h = 0;
    double err = 0;

    for (int i = 0; i < NUM_OF_VAR; i++) {
        x[i] = x_0[i];
    }

    if (t == t_0) {
        return x;
    } else if (t < t_0) {
        h = -INIT_STEP;
    } else {
        h = INIT_STEP;
    }

    double *k_1 = malloc(sizeof(double) * NUM_OF_VAR);
    double *k_2 = malloc(sizeof(double) * NUM_OF_VAR);
    double *k_3 = malloc(sizeof(double) * NUM_OF_VAR);
    double *k_4 = malloc(sizeof(double) * NUM_OF_VAR);
    double *k_5 = malloc(sizeof(double) * NUM_OF_VAR);
    double *k_6 = malloc(sizeof(double) * NUM_OF_VAR);

    while ((h < 0 && t < t_0) || (h > 0 && t > t_0)) {
        ode(k_1, x, t_0);
        for (int i = 0; i < NUM_OF_VAR; i++) {
            x_temp[i] = x[i] + k_1[i] * h / 2.0;
        }
        ode(k_2, x_temp, t_0 + 0.5*h);
        for (int i = 0; i < NUM_OF_VAR; i++) {
            x_temp[i] = x[i] + (k_1[i] + k_2[i]) * h / 4.0;
        }
        ode(k_3, x_temp, t_0 + 0.5*h);
        for (int i = 0; i < NUM_OF_VAR; i++) {
            x_temp[i] = x[i] + (-k_2[i] + 2*k_3[i]) * h / 2197.0;
        }
        ode(k_4, x_temp, t_0 + h);
        for (int i = 0; i < NUM_OF_VAR; i++) {
            x_temp[i] = x[i] + (7*k_1[i] + 10*k_2[i] + k_4[0]) * h / 27.0;
        }
        ode(k_5, x_temp, t_0 + 2/3.0*h);
        for (int i = 0; i < NUM_OF_VAR; i++) {
            x_temp[i] = x[i] + (28*k_1[i] - 125*k_2[i] + 546*k_3[i] + 54*k_4[i] - 378*k_5[i]) * h / 625.0;
        }
        ode(k_6, x_temp, t_0 + 0.2*h);

        for (int i = 0; i < NUM_OF_VAR; i++) {
            err += (-42*k_1[i] - 224*k_3[i] - 21*k_4[i] + 162*k_5[i]/50.0 + 125*k_6[i]) *
                   (-42*k_1[i] - 224*k_3[i] - 21*k_4[i] + 162*k_5[i]/50.0 + 125*k_6[i]) * h*h / 112896.0;
        }
        err = pow(err, 0.5);

        if (err <= err_tol || fabs(h) < MIN_STEP) {
            for (int i = 0; i < NUM_OF_VAR; i++) {
                x[i] += (14*k_1[i] + 35*k_4[i] + 162*k_5[i] + 125*k_6[i]) * h / 336.0;
            }
            t_0 += h;
        } else {
            h *= 0.9*pow(err_tol / err, 1/5.0);
        }

        err = 0;
    }

    free(x_temp);
    free(k_1);
    free(k_2);
    free(k_3);
    free(k_4);
    free(k_5);
    free(k_6);

    return x;
}

double *shoot(ODE ode, BOUND low_bound, BOUND upp_bound, SOLVER solver, double err_or_steps) {
    /*
        ode             : function defining system of ODEs
        low_bound       : lower boundary conditions to define non-free variables and initialise x_0
        upp_bound       : upper boundary conditions to compute the error of an approximation
        solver          : the solver used (euler, rk23, or rk45)
        err_or_steps    : error tolerance for rk or number of steps for euler
    */

    double *x_0 = malloc(sizeof(double) * NUM_OF_VAR);
    double *x;
    double *err = malloc(sizeof(double) * NUM_OF_FREE);     // discrepancy between estimated and actual x(upp_t)
    double *derr = malloc(sizeof(double) * NUM_OF_FREE);    // difference between discrepancies 
    double **J = malloc(sizeof(double *) * NUM_OF_FREE);    // the Jacobian
    for (int i = 0; i < NUM_OF_FREE; i++) {
        J[i] = malloc(sizeof(double) * NUM_OF_FREE);
    }

    low_bound(x_0, FREE_VAL, LOW_T);

    while (1) {
        x = solver(ode, x_0, LOW_T, UPP_T, err_or_steps);
        upp_bound(err, x, UPP_T);

        for (int i = 0; i < NUM_OF_FREE; i++) {
            if (err[i] >= DISCREPANCY) {
                break;
            }
            goto end_while;
        }

        // Optimisation w/ Newton-Raphson
        // Finding the Jacobian
        for (int i = 0; i < NUM_OF_FREE; i++) {
            FREE_VAL[i] += STEP_SIZE;
            low_bound(x_0, FREE_VAL, LOW_T);

            x = solver(ode, x_0, LOW_T, UPP_T, err_or_steps);
            upp_bound(derr, x, UPP_T);
            for (int j = 0; j < NUM_OF_FREE; j++) {
                J[j][i] = (derr[j] - err[j]) / STEP_SIZE;
            }

            // Reset the free values for the other partial derivatives
            FREE_VAL[i] -= STEP_SIZE;
        }
        
        // Solving for dfree
        /*
            I'm sure there's a more efficient way to implement Gaussian elimination,
            this was just the most straightforward
        */
        // 1. Elimination w/ partial pivoting
        for (int i = 0, j = 0; i < NUM_OF_FREE - 1 && j < NUM_OF_FREE - 1; i++, j++) {
            // Determining the pivot
            double pivot = J[i][j];
            int pivot_i = i;

            for (int k = i + 1; k < NUM_OF_FREE; k++) {
                if (abs(J[k][j]) > abs(pivot)) {
                    pivot = J[k][j];
                    pivot_i = k;
                }
            }

            // Swap
            if (pivot_i != i) {
                double *temp_row = J[i];
                J[i] = J[pivot_i];
                J[pivot_i] = temp_row;

                double temp_val = err[i];
                err[i] = err[pivot_i];
                err[pivot_i] = temp_val;
            }

            // Multiply and add
            for (int k = i + 1; k < NUM_OF_FREE; k++) {
                double coefficient = J[k][j] / J[i][j];
                J[k][j] = 0;

                for (int l = j + 1; l < NUM_OF_FREE; l++) {
                    J[k][l] -= coefficient * J[i][l];
                }
                err[k] -= coefficient * err[i];
            }
        }

        // 2. Backsubstitution
        for (int i = NUM_OF_FREE - 1, j = NUM_OF_FREE - 1; i >= 0; i--, j--) {
            double dfree = 0;
            dfree = err[i];
            for (int k = NUM_OF_FREE - 1; k > j; k--) {
                dfree -= J[i][k] * x[k];
            }
            dfree /= J[i][j];

            FREE_VAL[j] -= dfree; // -= since J(dfree) = -F but dfree is the solution for +F
        }

        low_bound(x_0, FREE_VAL, LOW_T);
    }

    end_while:
    free(err);
    free(derr);
    for (int i = 0; i < NUM_OF_FREE; i++) {
        free(J[i]);
    }
    free(J);

    return x_0;
}