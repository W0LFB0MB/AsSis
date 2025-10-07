#include <math.h>
#include <stdio.h>
#include <stdarg.h>

typedef int (*ColourTransition)(int t, int tMax);

// Transition from one colour to another
int transitionColour(double progress, int from, int to);

// Transition between each colour in arrays
int transitionColoursArray(int t, int tMax, int n, int *colours);

// Variadic alternative to transitionColoursArray
int transitionColours(int t, int tMax, int n, ...);

// Transition between pink and pink
int coolTransition(int t, int tMax);

// Transition between pink and yellow
int peachTransition(int t, int tMax);

// Transition between red, gree, and blue
int rgbTransition(int t, int tMax);

// Transition between the colours of the rainbow
int rainbowTransition(int t, int tMax);

// Alternates between the cool and peach transitions
int coolPeachTransition(int t, int tMax);
