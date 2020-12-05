#include <cstdio>
#include <cmath>
#include "Func.h"
#include "Dekker.h"
#include "Chebyshev.h"
#include "Remez.h"
#include "Matrix.h"
#include <random>
#include "LeastSquares.h"
#include "LeastSquaresPoly.h"
#include "Vector.h"
#include "Newton.h"
#include "NewtonMulti.h"

void remezTest()
{
    Function f(
        [](double x ) {return exp(x);},
        [](double x ) {return exp(x);}
    );
    f.rescale(-1,1);
    Poly P = Chebyshev::Approx(f.r,5);
    std::cout << P.toString() << std::endl;
    Poly P1 = Remez::Refine(P,f, false);
    std::cout << P1.toString() << std::endl;;
}

void testElim() {
    //https://courses.engr.illinois.edu/cs357/su2013/lectures/lecture07.pdf
    std::vector<double> v;
    for (int i=0; i<100; i++) v.push_back(random());
    //Matrix A(4,4,{2,4,-2,-2,1,2,4,-3,-3,-3,8,-2,-1,1,6,-3});
    //Vector b({-4,5,7,7});
    Matrix A(10,10,v);
    std::vector<double> v2;
    for (int i=0; i<10; i++) v2.push_back(random());
    Vector b(v2);
    //Matrix A(2,2,{2,2e20,1,1});
    //Vector b({2e20,2});
    A.ElimComplete(b);
    std::cout << A.toString() << std::endl;
    std::cout << b.toString() << std::endl;
    fflush(stdout);
}

void lstest() {
    std::mt19937 mt_rand(0);
    std::uniform_real_distribution<double> dist(-0.01,0.01);
    for (int i=0; i<100; i++)
        std::cout << dist(mt_rand) << std::endl;
    std::vector<double> x,y;
    for (int i=0; i<10; i++) {
        x.push_back((i-5)/10.0);
        y.push_back(2*x.back()+3+dist(mt_rand));
    }
    LeastSquares ls;
    ls.compute(Vector(x),Vector(y));
    std::cout << ls.a << " " << ls.b << std::endl;
}

void lsptest() {
    std::mt19937 mt_rand(0);
    std::uniform_real_distribution<double> dist(-0.01,0.01);
    std::vector<double> X,Y;
    double x = -1;
    while (x<=1){
        X.push_back(x);
        Y.push_back(exp(x));
        x+=0.0001;
    }
    LeastSquaresPoly lsp;
    Poly poly1 = lsp.compute(Vector(X),Vector(Y),4);
    std::cout << poly1.toString() << std::endl;
}

void testNewton() {
    Newton newt([](double x ) {return x*x-2;},[](double x ) {return 2*x;});
    double x = newt.find(1.3,1e-12);
    std::cout << x << std::endl;

    FunctionMulti func(2);
    func.F = {
            [](Vector X) { return atan(X[0]) - X[1] * X[1] * X[1]; },
            [](Vector X) { return 4 * X[0] * X[0] + 9 * X[1] * X[1] - 36; }
    };
    func.dF = {
            [](Vector X) { return 1 / (1 + X[0] * X[0]); },
            [](Vector X) { return -3*X[1]*X[1] ; },
            [](Vector X) { return 8 * X[0]; },
            [](Vector X) { return 18 * X[1]; }
    };
    NewtonMulti newton(func);
    Vector start({ 2.75, 1.25 });
    Vector X = newton.find(start, 1e-12);
    std::cout << X.toString() << std::endl;
}

int main() {
    remezTest();
}
