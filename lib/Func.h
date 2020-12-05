#pragma once
#pragma once
#include <functional>
#include "Vector.h"

typedef std::function <double( double )> Flambda;
typedef std::function <double( Vector )> FlambdaMulti;
//typedef std::function <double( int,Vector )> FlambdaMulti;
//typedef std::function <double( int,Vector )> FlambdaMultiD;

class Function {
    double a=1,b=0;
    double from=-1,to=1;
public:
    Flambda f;
    Flambda df;
    Flambda r;
    Flambda dr;
    Function(Flambda f, Flambda df);
    void rescale(double from , double to);
};

class FunctionMulti {
public:
    int size() {return F.size();}
    explicit FunctionMulti(int n);
    std::vector<FlambdaMulti> F;
    std::vector<FlambdaMulti> dF;
};