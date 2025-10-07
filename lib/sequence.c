#include "sequence.h"

double constantGenerator(int t) {
    return 1;
}

double binaryGenerator(int t) {
    return t % 2;
}

double patternGenerator(int t) {
  return t % 2 == 1 ? 3 : 1.3;
}
