#include "colours.h"

int transitionColour(double progress, int from, int to) {
  // limit progress to 0 <= progress <= 1
  progress = fabs(progress);
  progress = progress > 1 ? 1 : progress;

  // Deconstruct from colour
  int fromR = from & 0xFF;
  int fromG = (from >> 8) & 0xFF;
  int fromB = (from >> 16) & 0xFF;
  int fromA = (from >> 24) & 0xFF;

  // Deconstruct to colour
  int toR = to & 0xFF;
  int toG = (to >> 8) & 0xFF;
  int toB = (to >> 16) & 0xFF;
  int toA = (to >> 24) & 0xFF;

  // Calculate differences in colours
  int diffR = toR - fromR;
  int diffG = toG - fromG;
  int diffB = toB - fromB;
  int diffA = toA - fromA;

  // Calculate transition of colourus
  int finalR = fromR + diffR * progress;
  int finalG = fromG + diffG * progress;
  int finalB = fromB + diffB * progress;
  int finalA = fromA + diffA * progress;

  return finalR | (finalG << 8) | (finalB << 16) | (finalA << 24);
}

int transitionColoursArray(double progress, int n, int points[n]) {
  int i = progress * (n - 1);
  return transitionColour(fmod(progress * (n - 1), 1), points[i], points[i + 1]);
}

int transitionColours(double progress, int n, ...) {
  va_list args;
  va_start(args, n); 
  int colours[n];
  for (int i = 0; i < n; i++) {
    colours[i] = va_arg(args, int);
  };
  va_end(args);

  return transitionColoursArray(progress, n, colours);
}

int coolTransition(double progress) {
  return transitionColour(progress, 0xFF00FFFF, 0x00FFFFFF);
}

int peachTransition(double progress) {
  return transitionColour(progress, 0xFF00FFFF, 0xFFFF00FF);
}

int rgbTransition(double progress) {
  return transitionColours(progress, 3, 0xFF0000FF, 0x00FF00FF, 0x0000FFFF);
}

int rainbowTransition(double progress) {
  return transitionColours(progress, 7, 0xFF0000FF, 0xFF7F00FF, 0xFFFF00FF, 0x00FF00FF, 0x0000FFFF, 0x4B00FFFF, 0x8B00FFFF);
}
