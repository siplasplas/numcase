#pragma once
#include "Vector.h"
#include "Func.h"

class NewtonMulti {
    int size;
    FunctionMulti fun;
public:
    explicit NewtonMulti(FunctionMulti &fun): fun(fun) {
        size = fun.size();
    }
    Vector find(Vector start, float_type eps);
    Vector find(Vector start, float_type eps, const Vector& weights);
};
