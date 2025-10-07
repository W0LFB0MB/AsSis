/* Algorithm system Signa in silico (AsSis) */
#include "AsSis.h"

const int defaultRes = 1000; // Default render resolution
const double defaultScale = 100;
const double targetScale = 900; // Target scale for rendered content if autoScale = tue
const bool autoScale = true;

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
  double complex E = cexp(2 * I * M_PI * r);
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

void clearScreen(display *d) {
  colour(d, 0x000000FF);
  block(d, 0, 0, getWidth(d), getHeight(d));
  colour(d, 0xFFFFFFFF);
}

void render(display *d, RunData *runData) {
  // Pretty colours
  colour(d, runData->colourTransition((double)runData->t / runData->tMax));

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
  SequenceGenerator x, 
  int m, 
  int n, 
  double r, 
  CouplingFunction h,
  ColourTransition ct
) {
  // Initialise run data
  RunData runData;
  runData.t = 1;
  runData.tMax = (n - m) - 1;
  runData.c = expressionAlgorithm(x, m, n, r, h);
  runData.colourTransition = ct;

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

int main(const int argn, char *args[argn]) {
  if (argn == 2 && args[1][0] == '-' && args[1][1] == '?') {
    printf("Usage: %s -r [Double] -m [Int] -n [Int] -c [Int] -s [Int] -t [Int]\n", args[0]);
    printf("-r = Scaling\n");
    printf("-m = Start time\n");
    printf("-n = End time\n");
    printf("-c = Coupling function\n");
    printf("   -> 0 shrinking\n");
    printf("   -> 1 square\n");
    printf("   -> 2 shrinking square\n");
    printf("   -> 3 circle\n");
    printf("   -> 4 shrinking circle\n");
    printf("   -> 5 square circle\n");
    printf("   -> 6 circle square\n");
    printf("-s = Sequence generator\n");
    printf("   -> 0 pattern??\n");
    printf("   -> 1 constant\n");
    printf("   -> 2 binary\n");
    printf("-t = Colour transition\n");
    printf("   -> 0 pink to purple\n");
    printf("   -> 1 pink to yellow\n");
    printf("   -> 2 rgb\n");
    printf("   -> 3 rainbow\n");
    return 0;
  }

  double r = 0.34;
  int m = 0;
  int n = 1000;
  int c = 0;
  int s = 0;
  int t = 0;

  // Read cli flags for customisation
  for (int i = 1; i < argn - 1; i += 2) {
    switch (args[i][1]) {
      case 'r': r = atof(args[i + 1]); break;
      case 'm': m = atoi(args[i + 1]); break;
      case 'n': n = atoi(args[i + 1]); break;
      case 'c': c = atoi(args[i + 1]); break;
      case 's': s = atoi(args[i + 1]); break;
      case 't': t = atoi(args[i + 1]); break;
      default: printf("Invalid flag\n");
    }
  }

  display *d = newDisplay("Algorithm system Signa in silico (AsSis)", defaultRes, defaultRes);

  // Select coupling function
  CouplingFunction cf;
  switch (c) {
    case 1: cf = squareCouple; break;
    case 2: cf = shrinkingSquareCouple; break;
    case 3: cf = circleCouple; break;
    case 4: cf = shrinkingCircleCouple; break;
    case 5: cf = squareCircleCouple; break;
    case 6: cf = circleSquareCouple; break;
    default: cf = shrinkingCouple;
  }

  // Select sequence generator
  SequenceGenerator sg;
  switch (s) {
    case 1: sg = constantGenerator; break;
    case 2: sg = binaryGenerator; break;
    default: sg = patternGenerator;
  }

  // Select colour transition
  ColourTransition ct;
  switch (t) {
    case 1: ct = peachTransition; break;
    case 2: ct = rgbTransition; break;
    case 3: ct = rainbowTransition; break;
    default: ct = coolTransition;
  }

  renderPattern(d, sg, m, n, r, cf, ct);

  freeDisplay(d);
  return 0;
}
