#include "NewtonMulti.h"
#include "Matrix.h"

Vector NewtonMulti::find(Vector start, float_type eps) {
    Vector weights(size);
    for (int i=0; i<size; i++) weights[i]=1;
    return find(start, eps, weights);
}

Vector NewtonMulti::find(Vector start, float_type eps, const Vector& weights) {
    Vector X = start.clone();
    Vector F(size);
    Matrix J(size, size);
    do
    {
        for (int i = 0; i < size; i++)
            F[i] = fun.F[i](X);
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                J.at(i, j) = fun.dF[i*fun.size()+j](X);
        J.ElimPartial(F);
        X -= F;
    } while (F.norm(weights) > eps);
    return X;
}