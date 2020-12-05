#pragma once
#include "Func.h"

class Dekker
{
    Flambda func;
    static float_type ffun(float_type a, float_type b, float_type fa, float_type fb);
    static float_type lfun(float_type b, float_type a, float_type fb, float_type fa);
    static float_type rfun(float_type b, float_type a, float_type d, float_type fb, float_type fa, float_type fd);
public:
	Dekker(Flambda func): func(func) {}
	float_type find(float_type x0, float_type x1, float_type eps);
};
