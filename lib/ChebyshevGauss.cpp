#include "ChebyshevGauss.h"
#include <cmath>
#include <cstdint>
#include <exception>

double ChebyshevGauss::findC(int j, int N) {
    float_type Pi;
    Pi = M_PI;
    float_type sum = 0;
    for (int k = 1; k <= N; k++) {
        float_type pp = (k-0.5)*Pi/N;
        float_type x = cos(pp);
        pp = (j*(k-0.5))*Pi/N;
        float_type w = cos(pp);
        float_type tmp = func(x)*w;
        sum += tmp;
    }
    return 2*sum/N;
}

int highestOneBit(uint32_t i) {
    i |= (i >> 1);
    i |= (i >> 2);
    i |= (i >> 4);
    i |= (i >> 8);
    i |= (i >> 16);
    return i - (i >> 1);
}

double ChebyshevGauss::findC(int degree) {
    int n = highestOneBit(degree) * 2;
    if (n == 0) n = 1;
    float_type prev = 0;
    while (n < 1000) {
        float_type res = findC(degree,n);
        float_type tmp = fabs((res-prev)/10);
        if (tmp<machineEps) {
            /*tmp = fabs(res)/10;
            if (tmp<machineEps)
                throw std::exception();
            else*/
                return res;
        }
        prev = res;
        n *= 2;
    }
    throw std::exception();
}