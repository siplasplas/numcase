#pragma once
#include "Func.h"

class Newton {
    Flambda func,dfunc;
public:
    Newton(Flambda func, Flambda dfunc): func(func),dfunc(dfunc) {}
    float_type find(float_type x0, float_type eps);
};
