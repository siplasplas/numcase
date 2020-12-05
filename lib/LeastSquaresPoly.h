#pragma once
#include <vector>
#include "Poly.h"
#include "Matrix.h"

class LeastSquaresPoly {
public:
    Poly compute(const Vector &X, const Vector &Y, int deg);
};
