#ifndef DEFS_H
#define DEFS_H

/*
    DON'T TOUCH ANYTHING HERE
*/

typedef enum {
    IVP,
    BVP
} ODE_TYPE;

typedef void (ODE)(double *, double *, double);
typedef double *(SOLVER)(ODE, double *, double, double, double);
typedef void (BOUND)(double *, double *, double);   // yes, this is the exact same as ODE;
                                                    // I just think this makes it clearer

#endif