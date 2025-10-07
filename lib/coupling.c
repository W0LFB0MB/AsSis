#include "coupling.h"

double complex shrinkingCouple(double complex u, double complex v, int t, int tMax) {
  double re = creal(u);
  double im = cimag(u);
  
  return (re + I * im) * (1.0 - ((double)t / tMax));
}

double complex squareCouple(double complex u, double complex v, int t, int tMax) {
  double re = creal(u);
  double im = cimag(u);

  if (t != 0) {
    if (t % 2 == 1) {
      re = creal(v);
    } else {
      im = cimag(v);
    }
  }
  
  return (re + I * im);
}

double complex shrinkingSquareCouple(double complex u, double complex v, int t, int tMax) {
    u = shrinkingCouple(u, v, t, tMax);
    u = squareCouple(u, v, t, tMax);
    return u;
}

double complex circleCouple(double complex u, double complex v, int t, int tMax) {
  double re = creal(u);
  double im = cimag(u);

  double progress = ((double)t / tMax);
  double rad = progress * M_PI;
  re += sin(rad * 2) * 2;
  im += cos(rad * 2) * 2;
  
  return (re + I * im);
}

double complex shrinkingCircleCouple(double complex u, double complex v, int t, int tMax) {
    u = circleCouple(u, v, t, tMax);
    u = shrinkingCouple(u, v, t, tMax);
    return u;
}

double complex squareCircleCouple(double complex u, double complex v, int t, int tMax) {
    u = circleCouple(u, v, t, tMax);
    u = squareCouple(u, v, t, tMax);
    return u;
}

double complex circleSquareCouple(double complex u, double complex v, int t, int tMax) {
    u = squareCouple(u, v, t, tMax);
    u = circleCouple(u, v, t, tMax);
    return u;
}
