#include "coupling.h"

double complex shrinkingCouple(double complex u, double complex v, int t) {
  double re = creal(u);
  double im = cimag(u);
  
  return (re + I * im) * (1.0 - ((double)t / 1000));
}

double complex squareCouple(double complex u, double complex v, int t) {
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

double complex shrinkingSquareCouple(double complex u, double complex v, int t) {
    u = shrinkingCouple(u, v, t);
    u = squareCouple(u, v, t);
    return u;
}

double complex circleCouple(double complex u, double complex v, int t) {
  double re = creal(u);
  double im = cimag(u);

  double progress = ((double)t / 1000);
  double rad = progress * M_PI;
  re += sin(rad * 2) * 2;
  im += cos(rad * 2) * 2;
  
  return (re + I * im);
}

double complex shrinkingCircleCouple(double complex u, double complex v, int t) {
    u = circleCouple(u, v, t);
    u = shrinkingCouple(u, v, t);
    return u;
}
