#pragma once
#include "Func.h"
#include <cmath>

class ChebyshevGauss {
    Flambda func;
    double findC(int j, int N);
public:
    explicit ChebyshevGauss(Flambda  func): func(func){}
    double findC(int degree);
};
