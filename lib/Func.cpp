#include "Func.h"
#include <cmath>

Function::Function(Flambda f, Flambda df):f(f), df(df){
}

void Function::rescale( double from , double to) {
    a = (to-from)/(this->to-this->from);
    b = (from+to)/2-(this->from+this->to)/2;
    this->from = from;
    this->to = to;
    r = [this](double x ) {
        return f(a*x+b);
    };
    dr = [this](double x ) {
        return a*df(a*x+b);
    };
}


FunctionMulti::FunctionMulti(int n) {
    F.resize(n);
    dF.resize(n*n);
}