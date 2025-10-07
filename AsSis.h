#include <complex.h>
#define _USE_MATH_DEFINES 
#include <math.h>
#include <unistd.h>
#include <string.h>
#include "lib/display.h"
#include "lib/colours.h"
#include "lib/coupling.h"
#include "lib/sequence.h"

#ifndef M_PI
#   define M_PI 3.14159265358979323846
#endif

typedef struct RunData {
  int t;
  int tMax;
  double complex *c;
  double scale;
  ColourTransition colourTransition;
} RunData;

// Pattern / series generator
double pattern(int t);

// Coupling function ( I don't know what this is )
double complex couple(double complex u, double complex v, const int t);

// Generate sequence of points on the complex plane
double complex *expressionAlgorithm(
  SequenceGenerator x, 
  int m, 
  int n, 
  double r, 
  CouplingFunction h
);

// Return colour string from individual components
int getColour(int r, int g, int b, int a);

// Clears the screen
void clearScreen(display *d);

// Render one point on the pattern to the screen
void render(display *d, RunData *runData);

// Handle keypress & render loop iterations
bool runIterationHander(display *d, void *runData, const char c);

// Render a pattern
void renderPattern(
  display *d, 
  SequenceGenerator x, 
  int m, 
  int n, 
  double r, 
  CouplingFunction h,
  ColourTransition ct
);
