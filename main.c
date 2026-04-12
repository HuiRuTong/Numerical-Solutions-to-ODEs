#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "DEFS.h"
#include "CONFIG.h"
#include "SOLVER.h"
#include "SOLVE.h"

int main(int argc, char *argv[]) {
    if (argc > 7) {
        printf("Invalid number of arguments!\n");
        exit(0);
    }

    if(strcmp(argv[1], "0") && strcmp(argv[1], "1")) {
        printf("Invalid arguments!\n");
        exit(1);  
    }
    
    // I'm not checking if the entred params are coherent numbers
    // No one would be that stupid anyway, right?
    for (int i = 2; i < 6; i++) {
        int j = 0;
        while (argv[i][j] != '\0') {
            if (!isdigit(argv[i][j]) && argv[i][j] != '.' && argv[i][j] != '-' && argv[i][j] != 'e') {
                printf("Invalid arguments!\n");
                exit(1);
            }
            j++;
        }
    }

    ODE_TYPE problem = atoi(argv[1]);
    double low_lim = atof(argv[2]);
    double upp_lim = atof(argv[3]);
    double err_or_steps = atof(argv[4]);
    int num_of_pts = atoi(argv[5]);
    FILE *output = fopen("results.txt", "w");

    printf("Writing to file. Do not close the program.\n");
    time_t begin = time(NULL);
    if (problem == IVP) {
        if (!strcmp(argv[6], "euler")) {
            solve_ivp(output, ode, euler, X_INIT, T_INIT, low_lim, upp_lim, err_or_steps, num_of_pts);
        } else if (!strcmp(argv[6], "rk23")) {
            solve_ivp(output, ode, rk23, X_INIT, T_INIT, low_lim, upp_lim, err_or_steps, num_of_pts);
        } else if (!strcmp(argv[6], "rk45")) {
            solve_ivp(output, ode, rk45, X_INIT, T_INIT, low_lim, upp_lim, err_or_steps, num_of_pts);
        } else {
            printf("Invalid arguments!\n");
            exit(1);
        }
    } else {
        if (argc == 7) {
            printf("Invalid number of arguments!\n");
            exit(0);
        }

        solve_bvp(output, ode, low_bound, upp_bound, rk23, low_lim, upp_lim, err_or_steps, num_of_pts);
    }
    time_t end = time(NULL);
    printf("Time taken: %ld epochs\n", (end - begin));
    
    /*
        If you need high-precision, rk45 & err_tol <= 1e-8 is the way to go
        If you're aiming for decent precision w/ minimal time, use rk23 and err_tol = 1e-6
        Euler is only here because it takes little effort to implement. Do NOT use it.
        Like, it works, but it's slow, inaccurate, and bitchless.
    */
}