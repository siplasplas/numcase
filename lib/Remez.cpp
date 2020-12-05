#include <limits>
#include "Remez.h"
#include "Dekker.h"
#include "Matrix.h"

using namespace std;

void Remez::FindExtremes(std::vector<float_type> &extremes, const Poly &poly, Flambda func) {
    float_type x = -1;
    float_type step = 1.0/poly.getDeg();
    float_type xstep = x+step;
    float_type t = machineEps;
    extremes[0] = -1;
    int cnt = 1;
    float_type tmp = 1;
    Flambda h = [poly,func](double x ) {
        return poly.dhorner(x) - func(x);
    };
    while (x<tmp) {
        Dekker dekker(h);
        float_type mpx = dekker.find(x, xstep, t);
        if (!isnan(mpx)) {
            if (cnt>=extremes.size()) throw std::exception();
            extremes[cnt] = mpx;
            cnt++;
        }
        x = xstep;
        xstep += step;
    }
    if (cnt>=extremes.size()+1) throw std::exception();
    if (cnt>=extremes.size())
        extremes.push_back(cnt);
    else
        extremes[cnt] = 1;
}

void Remez::Coefficients(Poly &result, Flambda func, vector<float_type> &extremes, float_type initialSign, int relative)
{
    int N = result.getDeg() + 2;
    Vector b(N);
    Matrix A(N,N);
    float_type sign = -initialSign;
    for (int i = 0; i < N; i++)
    {
        float_type power = 1;
        for (int j = 0; j < N-1; j++)
        {
            A.at(i,j) = power;
            power *= extremes[i];
        }
        if (relative)
        {
            float_type tmp = fabs(func(extremes[i]))*sign;
            A.at(i,N-1) = tmp;
        }
        else
            A.at(i,N-1) = sign;
        b[i] = func(extremes[i]);
        sign *= -1;
    }
    A.ElimComplete(b);
    result = Poly::init(b.getStd(), N-2);
}

Poly Remez::Refine(const Poly &given, const Function &func, bool relative) {
    vector<float_type> extremes(given.getDeg()+2);
    Poly result = given;
    while(true) {
        FindExtremes(extremes, result, func.dr);
        float_type MinDiff = numeric_limits<float_type>::max();
        float_type MaxDiff = 0;
        Flambda h = [result,func](double x ) {
            return result.horner(x) - func.r(x);
        };
        for (int i = 0; i < extremes.size(); i++) {
            float_type e = fabs(h(extremes[i]));
            if (relative) {
                e = fabs(e/func.r(extremes[i]));
            }
            if (e<MinDiff)
                MinDiff = e;
            if (e>MaxDiff)
                MaxDiff = e;
        }
        float_type tmp = MaxDiff/MinDiff;
        float_type tmp2 = 1.0001;
        if (tmp<tmp2) break;
        tmp = h(-1);
        int initialSign;
        if (tmp<0) initialSign = -1; else initialSign = 1;
        Coefficients(result, func.r, extremes, initialSign, relative);
    }
    return result;
}
