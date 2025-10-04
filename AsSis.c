/* Algorithm system Signa in silico (AsSis) */
#include "AsSis.h"

const int defaultRes = 1000; // Default render resolution
const double targetScale = 900; // Target scale for rendered content

const bool squarify = false; // Squarify???
const int m = 0; // Start rendering from
const int n = 1000; // Stop rendering at
const double r = 334.34; // Changing this doesn't seem to change anything???

int x(int t) {
  return (t % 2);        // 0 or 1, triangular type pattern
  // return t % 2 ? 1 : -1; // -1 or 1
  // return (t % 3) - 1; // From -1 to 1, vertical ribon like output
  // return t % 100;
}

double complex couple(double complex u, double complex v, int t) {
  // Progress to n, min 0, max 1;
  double progress = ((double)(t - m) / (n - m));
  double rad = progress * M_PI;
  double scale = 0.4;

  double re = creal(u) * scale + sin(rad * 2) * 0.9;
  double im = cimag(u) * scale + cos(rad * 2) * 0.9;

  // Squarify the output???
  if (squarify && t % 2 == 1) {
    re = creal(v);
  }
  
  return (re + I * im);
}

double complex *expressionAlgorithm(double r) {
  // I don't know how, but it works, I think...
  int max = n - m;
  double complex *c = malloc(max * sizeof(double complex));
  double complex E = cos(2 * M_PI * r) + I * sin(2 * M_PI * r);
  double complex u = cpow(E, x(m));
  double complex v = u;
  c[m] = v;
  for (int t = 0; t < max; t++) {
    u = u * cpow(E, x(t));
    v = couple(u, v, t);
    c[t] = v;
  }
  return c;
}

int getColour(int r, int g, int b, int a) {
  return a | (b << 8) | (g << 16) | (r << 24);
}

const int white = 0xFFFFFFFF;
const int black = 0x00000000;

void clearScreen(display *d) {
  colour(d, black);
  block(d, 0, 0, getWidth(d), getHeight(d));
  colour(d, white);
}

void render(display *d, RunData *runData) {
  int t = runData->t;

  // Pretty colours
  double colourStep = 255.0 / (n - m);
  colour(d, getColour(colourStep * (t - m), 255.0 - (colourStep * (t - m)), 0xFF, 0xFF));
  
  // Render line
  double scale = runData->scale;
  line(d, 
    creal(runData->c[t-1]) * scale + (getWidth(d) / 2), // x0
    -cimag(runData->c[t-1]) * scale + (getHeight(d) / 2), // y0
    creal(runData->c[t]) * scale + (getWidth(d) / 2), // x1
    -cimag(runData->c[t]) * scale + (getHeight(d) / 2)// y1
  );
  show(d);
}

bool runIterationHander(display *d, void *runData, const char c) {
  // A way to escape
  if (c == 'x') return true;

  // Clear screen & re-render
  if (c == 'r') {
    clearScreen(d);
    ((RunData *)runData)->t = 1;
  }
  
  // Stop rendering at max t
  if (((RunData *)runData)->t < n - m) {
    render(d, runData);
    ((RunData *)runData)->t += 1;
  } 

  return false;
}

int main(void) {
  display *d = newDisplay("Algorithm system Signa in silico (AsSis)", defaultRes, defaultRes);

  // Initialise run data
  RunData runData;
  runData.t = 1;
  runData.c = expressionAlgorithm(r);

  // Find largest point for auto scaling
  double largest = 0;
  for (int i = m; i < n; i++) {
    double real = fabs(creal(runData.c[i]));
    if (largest < real) largest = real;
    double imaginary = fabs(cimag(runData.c[i]));
    if (largest < imaginary) largest = imaginary;
  }
  runData.scale = (targetScale / largest) / 2;

  // Begin the render loop
  run(d, &runData, runIterationHander);

  // Free allocated memory
  free(runData.c);
  freeDisplay(d);
  return 0;
}
