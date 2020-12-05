#pragma once
#pragma once
#include <functional>
#include "Vector.h"

typedef std::function <float_type( float_type )> Flambda;
typedef std::function <float_type( Vector )> FlambdaMulti;
//typedef std::function <float_type( int,Vector )> FlambdaMulti;
//typedef std::function <float_type( int,Vector )> FlambdaMultiD;

class Function {
    float_type a=1,b=0;
    float_type from=-1,to=1;
public:
    Flambda f;
    Flambda df;
    Flambda r;
    Flambda dr;
    Function(Flambda f, Flambda df);
    void rescale(float_type from , float_type to);
};

class FunctionMulti {
public:
    int size() {return F.size();}
    explicit FunctionMulti(int n);
    std::vector<FlambdaMulti> F;
    std::vector<FlambdaMulti> dF;
};