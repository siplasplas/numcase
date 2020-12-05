#pragma once
#include "Vector.h"

class LeastSquares {
public:
    double a,b;
    void compute(const Vector &X, const Vector &Y);
};

