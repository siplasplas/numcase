#include "LeastSquares.h"
#include <cassert>

void LeastSquares::compute(const Vector &X, const Vector &Y) {
    double Sx = 0, Sy = 0, Sxx = 0, Sxy = 0;
    int n = X.getRows();
    assert(Y.getRows()==n);
    for (int i = 0; i < n; i++) {
        Sx = Sx + X[i];
        Sy = Sy + Y[i];
        Sxx = Sxx + X[i] * X[i];
        Sxy = Sxy + X[i] * Y[i];
    }
    double Delta = Sx * Sx - Sxx * n;
    a = (Sx * Sy - Sxy * n) / Delta;
    b = (Sx * Sxy - Sxx * Sy) / Delta;
}
