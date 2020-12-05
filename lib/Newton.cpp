#include "Newton.h"

float_type Newton::find(float_type x0, float_type eps) {
    float_type x = x0;
    float_type delta = 0;
    do
    {
        delta = func(x)/dfunc(x);
        x -= delta;
    } while (fabs(delta) > eps);
    return x;
}