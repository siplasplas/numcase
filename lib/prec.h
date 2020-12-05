#pragma once

//#define USE_MP

#ifdef USE_MP
#include <mpcpp/mpfrcpp.h>
using namespace mpfr;
typedef Mpfr float_type;
const int PREC_BITS=53;
#define INFINITY const_infinity()
#define NAN float_type().setNan()
#define M_PI const_pi()
#else
#include <cmath>
typedef double float_type;
const int PREC_BITS=53;
#endif

const float_type machineEps = pow(2,-(PREC_BITS-1));
