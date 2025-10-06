#include <math.h>
#include <stdio.h>
#include <stdarg.h>

// Transition from one colour to another
int transitionColour(double progress, int from, int to);

// Transition between each colour in arrays
int transitionColoursArray(double progress, int n, int *colours);

// Variadic alternative to transitionColoursArray
int transitionColours(double progress, int n, ...);

// Transition between pink and pink
int coolTransition(double cyan);

// Transition between red, gree, and blue
int rgbTransition(double progress);

// Transition between the colours of the rainbow
int rainbowTransition(double progress);
