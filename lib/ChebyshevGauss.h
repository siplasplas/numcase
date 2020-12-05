#pragma once
#include "Func.h"

class ChebyshevGauss {
    Flambda func;
    float_type findC(int j, int N);
public:
    explicit ChebyshevGauss(Flambda  func): func(func){}
    float_type findC(int degree);
};
