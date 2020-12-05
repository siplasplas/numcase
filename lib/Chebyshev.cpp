#include "Chebyshev.h"
#include "ChebyshevGauss.h"

Poly Chebyshev::genT(int n) {
    Poly T0(0);
    Poly T1(1);
    if (n<=0) return T0;
    for (int i=2; i<=n; i++) {
        Poly T2 = T1.up()*2 - T0;
        T0 = T1;
        T1 = T2;
    }
    return T1;
}

Poly Chebyshev::genU(int n) {
    Poly T0(0);
    Poly T1(1,2);
    if (n<=0) return T0;
    for (int i=2; i<=n; i++) {
        Poly T2 = T1.up()*2 - T0;
        T0 = T1;
        T1 = T2;
    }
    return T1;
}

Poly Chebyshev::Approx(Flambda func, int n) {
    ChebyshevGauss cg(func);
    Poly sum(0, 0.5*cg.findC(0));
    Poly T0(0);
    Poly T1(1);
    for (int j=1; j<=n; j++) {
        sum += T1*cg.findC(j);
        Poly T2 = T1.up()*2 - T0;
        T0 = T1;
        T1 = T2;
    }
    return sum;
}