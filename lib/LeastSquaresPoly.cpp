#include "LeastSquaresPoly.h"
#include <cassert>
#include <cmath>

Poly LeastSquaresPoly::compute(const Vector &X, const Vector &Y, int deg) {
    assert(X.getRows() == Y.getRows());
    int count = deg+1;
    Matrix A(X.getRows(), count);
    for (int i = 0; i < X.getRows(); i++)
        for (int j = 0; j < count; j++)
        {
            A.at(i, j) = pow(X[i], j);
        }//3.0000000000000009+1.9999999999999989*x+0.6999999999999896*x^2
    Matrix AtA = A.transposedMult(A);
    Vector AtY = A.transposedMult(Y);
    AtA.ElimComplete(AtY);
    Poly res(AtY.getStd());
    return res;
}
