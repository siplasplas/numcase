#pragma once
#include <vector>
#include <iostream>

#include "prec.h"

class Poly {
    int deg;
    std::vector<float_type> P;
public:
    Poly(){};
    Poly(int deg, double highest=1);
    Poly(const std::vector<float_type> &initArr);
    Poly operator*(double d);
    Poly operator+(const Poly &other);
    void operator+=(const Poly &other);
    Poly operator-(const Poly &other);
    double horner(double x) const;
    float_type dhorner(float_type x) const;
    int getDeg() const;
    Poly up();
    std::string toString();
    static Poly init(std::vector<float_type> v, int deg);
};