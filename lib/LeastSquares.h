#pragma once
#include "Vector.h"

class LeastSquares {
public:
    float_type a,b;
    void compute(const Vector &X, const Vector &Y);
};

