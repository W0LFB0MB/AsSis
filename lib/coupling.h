#include <complex.h>
#define _USE_MATH_DEFINES 
#include <math.h>

#ifndef M_PI
#   define M_PI 3.14159265358979323846
#endif

typedef double complex (*CouplingFunction)(double complex u, double complex v, int t);

// shrinks the output over time
double complex shrinkingCouple(double complex u, double complex v, int t);

// Forces lines to be either vertical or horizontal
double complex squareCouple(double complex u, double complex v, int t);

// Forces lines to be either vertical or horizontal while shrinking
double complex shrinkingSquareCouple(double complex u, double complex v, int t);

// Moves the output in a circle
double complex circleCouple(double complex u, double complex v, int t);

// Moves the output in a circle while shrinking
double complex shrinkingCircleCouple(double complex u, double complex v, int t);

// Moves the output in a circle, then forces lines to either be verticl or horrizontal
double complex squareCircleCouple(double complex u, double complex v, int t);

// Forces lines to either be verticl or horrizontal, then moves the output in a circle
double complex circleSquareCouple(double complex u, double complex v, int t);
