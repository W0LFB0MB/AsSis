#include <math.h>

typedef double (*SequenceGenerator)(int t);

// Always returns 1
double constantGenerator(int t);

// Returns 1 or 0
double binaryGenerator(int t);

// Returns 1 or 1.3
double patternGenerator(int t);
