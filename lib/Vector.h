#pragma once
#include <string>
#include <vector>

#include "prec.h"

class Vector {
    std::vector<float_type> v;
    int rows;
public:
    const std::vector<float_type>& getStd() {return v;}
    int getRows() const { return rows;}
    explicit Vector(int rows);
    explicit Vector(const std::vector<float_type> &initArr);
    Vector clone();
    float_type& operator[](int row);
    float_type at(int row) const;
    float_type operator[](int row) const;
    Vector operator+(const Vector &other);
    Vector operator-(const Vector &other);
    void operator+=(const Vector &other);
    void operator-=(const Vector &other);
    void swapRows(int r1, int r2);
    float_type norm();
    float_type norm(const Vector &weights);
    std::string toString();
};
