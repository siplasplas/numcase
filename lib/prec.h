#pragma once

#define USE_MP

#ifdef USE_MP
#include <mpcpp/mpfrcpp.h>
using namespace mpfr;
typedef Mpfr float_type;
const int PREC_BITS=53;
#undef INFINITY
#define INFINITY const_infinity()
#undef NAN
#define NAN float_type().setNan()
#undef M_PI
#define M_PI const_pi()
#else
#include <cmath>
typedef double float_type;
const int PREC_BITS=53;
#endif

inline void setDefPrec() {
#ifdef USE_MP
    set_default_prec(PREC_BITS);
#endif
}

const float_type machineEps = pow(2,-(PREC_BITS-1));
/*
//https://bytes.com/topic/c/answers/670460-machine-epsilon
Float 1.19209290e-07F // float 24-1 bit
Double 2.2204460492503131e-16 // float_type 53-1
Long Double 1.084202172485504434007452e-19L //float_type 64-1 bit
*/