#include <math.h>
#include "FloatHelper.h"

float EPSILON = 0.0001;

bool areEqual(float a, float b) {
    return fabs(a -b) < EPSILON;
}
