#pragma once
#include <string>
#include <vector>

#include "prec.h"

class Vector {
    std::vector<double> v;
    int rows;
public:
    const std::vector<double>& getStd() {return v;}
    int getRows() const { return rows;}
    explicit Vector(int rows);
    explicit Vector(const std::vector<double> &initArr);
    Vector clone();
    double& operator[](int row);
    double at(int row) const;
    double operator[](int row) const;
    Vector operator+(const Vector &other);
    Vector operator-(const Vector &other);
    void operator+=(const Vector &other);
    void operator-=(const Vector &other);
    void swapRows(int r1, int r2);
    double norm();
    double norm(const Vector &weights);
    std::string toString();
};
