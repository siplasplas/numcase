#include "Func.h"

Function::Function(Flambda f, Flambda df):f(f), df(df){
}

void Function::rescale( float_type from ,float_type to) {
    a = (to-from)/(this->to-this->from);
    b = (from+to)/2-(this->from+this->to)/2;
    this->from = from;
    this->to = to;
    r = [this](float_type x ) {
        return f(a*x+b);
    };
    dr = [this](float_type x ) {
        return a*df(a*x+b);
    };
}


FunctionMulti::FunctionMulti(int n) {
    F.resize(n);
    dF.resize(n*n);
}