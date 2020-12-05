#pragma once
#include "Poly.h"
#include "Func.h"

class Chebyshev {
public:
    static Poly genT(int n);
    static Poly genU(int n);
    static Poly Approx(Flambda func, int n);
};
