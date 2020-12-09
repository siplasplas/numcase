#include <cassert>
#include "Dekker.h"
#include <iostream>

#define DIFFSIGN(a,b) (a <= 0 && b >= 0 || a >= 0 && b <= 0)

bool between(float_type x, float_type a, float_type b)
{
    if (b > a)
        return (x >= a && x <= b);
    else
        return (x >= b && x <= a);
}

float_type hfun(float_type b, float_type c)
{
    assert(b != c);
    if (c > b)
        return b + fabs(b*machineEps);
    else
        return b - fabs(b*machineEps);
}

float_type mfun(float_type b, float_type c)
{
    return 0.5*(b + c);
}

float_type Dekker::lfun(float_type b, float_type a, float_type fb, float_type fa)
{
    if (fb != fa)
        return b - fb*(b - a) / (fb - fa); //secant method;
    else if (fa != 0)
        return INFINITY;
    else return b;
}

float_type Dekker::ffun(float_type a, float_type b, float_type fa, float_type fb)
{
    assert(a != b);
    return (fa - fb) / (a - b);
}

float_type Dekker::rfun(float_type b, float_type a, float_type d, float_type fb, float_type fa, float_type fd)
{
    float_type alpha = ffun(b, d, fb, fd)*fa;
    float_type beta = ffun(a, d, fa, fd)*fb;
    if (beta != alpha)
    {
        return b - beta*(b - a) / (beta - alpha);
    }
    else if (alpha != 0)
        return INFINITY;
    else
        return 0; //beta == alpha == 0
}

float_type wfun(float_type l, float_type b, float_type c)
{
    float_type h = hfun(b, c);
    float_type m = mfun(b, c);
    if (between(l, h, m))
    {
        return l;
    }
    else if (fabs(l - b) <= fabs(b*machineEps) && !between(l, b, m))
    {
        return h;
    }
    else
    {
        return m;
    }
}

float_type Dekker::find(float_type x0, float_type x1, float_type eps)
{
    int itercnt;
    float_type x, xp, fx, fxp, a, b, c, fa, fb;
    float_type lambda, rho, d, fd;
    itercnt = 0;
    //initialization
    fxp = func(x0);
    fx = func(x1);
    if (x0 == x1) return fx;
    if (!DIFFSIGN(fx, fxp)) return NAN;

    if (fabs(fx) <= fabs(fxp))
    {
        b = x1;
        a = c = x0;
        fa = fxp;
        fb = fx;
    }
    else
    {
        b = x0;
        a = c = x1;
        fa = fx;
        fb = fxp;
    }
    float_type xk = xp = x0;
    float_type fxk = fxp;
    x = x1;

    d = NAN;
    fd = NAN;
    itercnt = 1;
    int age = 0;
    float_type bp = b;
    float_type cp = c;
    float_type ap = a;
    float_type fap, fbp;
    while (fabs(b - c) > 2 * eps)
    {
        itercnt++;
        age++;
        if (fabs(b - c) <= (0.5 + 2 * machineEps)*(fabs(bp - cp) + fabs(b)*machineEps))
            age = 1;
        xp = x;
        if (itercnt == 2)
        {
            lambda = lfun(b, a, fb, fa);
            if (fabs(lambda - b) < fabs(b*machineEps)) break;
            x = wfun(lambda, b, c);
        }
        else if (itercnt >= 3 && age <= 3)
        {
            rho = rfun(b, a, d, fb, fa, fd);
            if (fabs(rho - b) < fabs(b*machineEps)) break;
            x = wfun(rho, b, c);
        }
        else if (itercnt >= 3 && age == 4)
        {
            rho = rfun(b, a, d, fb, fa, fd);
            if (fabs(rho - b) < fabs(b*machineEps)) break;
            x = wfun(2 * rho - b, b, c);
        }
        else
        {
            x = mfun(b, c);
        }

        fxp = fx;
        fx = func(x);

        if (DIFFSIGN(fxp, fx))
        {
            xk = xp;
            fxk = fxp;
        }

        bp = b;
        fbp = fb;
        ap = a;
        fap = fa;
        cp = c;
        if (fabs(fx) <= fabs(fxk))
        {
            a = b;
            fa = fb;
            b = x;
            fb = fx;
            c = xk;
        }
        else
        {
            b = xk;
            fb = fxk;
            a = c = x;
            fa = fx;
        }

        if (b == x || b == bp)
        {
            d = ap;
            fd = fap;
        }
        else
        {
            d = bp;
            fd = fbp;
        }
    }
    return b;
}

