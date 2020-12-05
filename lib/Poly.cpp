#include "Poly.h"
#include <algorithm>
#include <string>
#include <algorithm>

Poly::Poly(int deg, double highest): deg(deg) {
    P.resize(deg+1);
    P[deg] = highest;
}

Poly Poly::operator*(double d) {
    Poly result(deg);
    for (int i=0; i<=deg; i++)
        result.P[i] = P[i] * d;
    return result;
}

Poly Poly::operator+(const Poly &other) {
    int resdeg = std::max(deg, other.deg);
    Poly result(resdeg);
    for (int i=0; i<=resdeg; i++) {
        int sum;
        if (i>deg) sum = other.P[i];
        else if (i>other.deg) sum = P[i];
        else sum = P[i] + other.P[i];
        result.P[i] = sum;
    }
    return result;
}

void Poly::operator+=(const Poly &other) {
    if (other.deg>deg) {
        deg = other.deg;
        P.resize(other.deg+1);
    }
    int mindeg = std::min(deg, other.deg);
    for (int i=0; i<=mindeg; i++) {
        P[i] += other.P[i];
    }
}

//not check if subtract equal values and if highest coefficient is zero
Poly Poly::operator-(const Poly &other) {
    int resdeg = std::max(deg, other.deg);
    Poly result(resdeg);
    for (int i=0; i<=resdeg; i++) {
        int diff;
        if (i>deg) diff = -other.P[i];
        else if (i>other.deg) diff = P[i];
        else diff = P[i] - other.P[i];
        result.P[i] = diff;
    }
    return result;
}

Poly Poly::up() {
    Poly result(deg+1,P[deg]);
    for (int i=deg-1; i>=0; i--)
        result.P[i+1] = P[i];
    return result;
}

int Poly::getDeg() const {
    return deg;
}

double Poly::horner(double x) const{
    float_type result = P[deg];
    for (int i = deg - 1; i >= 0; i--)
    {
        result = result*x + P[i];
    }
    return result;
}

float_type Poly::dhorner(float_type x) const {
    float_type result = P[deg]*deg;
    for (int i = deg - 1; i >= 1; i--)
    {
        result = result*x + i*P[i];
    }
    return result;
}


#include <sstream>

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}

std::string Poly::toString() {
    std::string polyStr = "";
    if (P.size()==0) return polyStr;
    for (int i = 0; i <= deg; i++) {
        if (i>0) polyStr +="+";
        polyStr += to_string_with_precision(P[i],16);
        if (i>0) {
            polyStr += "*x";
            if (i>1)
                polyStr += "^"+std::to_string(i);
        }
    }
    return polyStr;
}

Poly Poly::init(std::vector<float_type> v, int deg) {
    Poly result(deg);
    for (int i=0; i<=std::min(deg,int(v.size())-1); i++)
        result.P[i] = v[i];
    return result;
}

Poly::Poly(const std::vector<float_type> &initArr) {
    P = initArr;
    deg = P.size()-1;
}
