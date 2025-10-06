/* Algorithm system Signa in silico (AsSis) */
#include "AsSis.h"

const int defaultRes = 1000; // Default render resolution
const double defaultScale = 100;
const double targetScale = 900; // Target scale for rendered content if autoScale = tue
const bool autoScale = true;

// Fun settings, can ignore if boring
const bool squarify = false; // Squarify???
const bool circlify = false; // Circlify???


double pattern(int t) {
  return t % 2 == 1 ? 3 : 1.3;
  // return 2.7;
  // return 0.1; // Circle?
  // return (t % 2);        // 0 or 1, triangular type pattern
  // return t % 2 ? 1 : -1; // -1 or 1
  // return (t % 3) - 1; // From -1 to 1, vertical ribon like output
  // return t % 100;
  // int pattern[] = { 2, 8, 4, 1, 3, -3, 5, 9, 3, 1, 2, 3, 8, 7, 8, -1, 5, -1, -3, -2, 9 };
  // return pattern[t % 21];
}

double complex couple(double complex u, double complex v, int t) {
  double re = creal(u);
  double im = cimag(u);

  // Move around in a circle
  if (circlify) {
    double progress = ((double)(t) / 1000);
    double rad = progress * M_PI;
    re += sin(rad * 2) * 2;
    im += cos(rad * 2) * 2;
  }

  // Make all lines either horizontal or vertical
  if (squarify && t != 0) {
    if (t % 2 == 1) {
      re = creal(v);
    } else {
      im = cimag(v);
    }
  }
  
  return (re + I * im) * (1.0 - ((double)t / 1000));
}

double complex *expressionAlgorithm(
  double x(int t), 
  int m, 
  int n, 
  double r, 
  complex double h(
    complex double u, 
    complex double v, 
    int t
  )
) {
  // I don't know how, but it works, I think...
  double complex *c = malloc((n - m) * sizeof(double complex));
  double complex E = cos(2 * M_PI * r) + I * sin(2 * M_PI * r);
  double complex u = cpow(E, x(m));
  double complex v = u;
  c[0] = v;

  for (int t = m; t < n; t++) {
    u = u * cpow(E, x(t));
    v = h(u, v, t);
    c[t - m] = v;
  }

  return c;
}

int getColour(int r, int g, int b, int a) {
  return a | (b << 8) | (g << 16) | (r << 24);
}

void clearScreen(display *d) {
  colour(d, 0x000000FF);
  block(d, 0, 0, getWidth(d), getHeight(d));
  colour(d, 0xFFFFFFFF);
}

void render(display *d, RunData *runData) {
  // Pretty colours
  colour(d, peachTransition((double)runData->t / runData->tMax));

  // Scale point
  complex double scaledPoint = runData->c[runData->t] * runData->scale;
  complex double scaledPrevPoint = runData->c[runData->t - 1] * runData->scale;
  
  // Render line
  int midWidth = getWidth(d) / 2;
  int midHeight = getHeight(d) / 2;
  line(d, 
    creal(scaledPoint) + midWidth, // x0
    -cimag(scaledPoint) + midHeight, // y0
    creal(scaledPrevPoint) + midWidth, // x1
    -cimag(scaledPrevPoint) + midHeight // y1
  );
  show(d);
}

bool runIterationHander(display *d, void *runData, const char c) {
  // A way to escape
  if (c == 'x') return true;

  // Render line
  render(d, runData);

  // Stop rendering at max t
  if (((RunData *)runData)->t < ((RunData *)runData)->tMax) {
    ((RunData *)runData)->t += 1;
  }

  // Clear screen & re-render
  if (c == 'r') {
    clearScreen(d);
    ((RunData *)runData)->t = 1;
  }

  return false;
}

void renderPattern(
  display *d, 
  double x(int t), 
  int m, 
  int n, 
  double r, 
  double complex h(
    double complex u, 
    double complex v, 
    const int t
  )
) {
  // Initialise run data
  RunData runData;
  runData.t = 1;
  runData.tMax = (n - m) - 1;
  runData.c = expressionAlgorithm(x, m, n, r, h);

  // Find largest point for auto scaling
  if (autoScale == true) {
    double largest = 0;
    for (int i = m; i < n; i++) {
      double real = fabs(creal(runData.c[i]));
      if (largest < real) largest = real;
      double imaginary = fabs(cimag(runData.c[i]));
      if (largest < imaginary) largest = imaginary;
    }
    runData.scale = (targetScale / largest) / 2;
  } else {
    runData.scale = defaultScale;
  }

  // Begin the render loop
  run(d, &runData, runIterationHander);

  // Free allocated memory
  free(runData.c);
}

int main(void) {
  display *d = newDisplay("Algorithm system Signa in silico (AsSis)", defaultRes, defaultRes);

  renderPattern(d, pattern, 0, 1000, 334.34, couple);

  freeDisplay(d);
  return 0;
}
