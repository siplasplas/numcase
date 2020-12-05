#pragma once
#include <vector>
#include "Func.h"
#include "Poly.h"

class Remez {
    static void FindExtremes(std::vector<float_type> &extremes, const Poly &poly, Flambda func);
    static void Coefficients(Poly &given, Flambda  func, std::vector<float_type> &extremes, float_type initialSign, int relative);
public:
    static Poly Refine(const Poly &given, const Function &func, bool relative);
};
