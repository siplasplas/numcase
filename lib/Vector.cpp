#include "Vector.h"
#include <cmath>

Vector::Vector(int rows):rows(rows) {
    v.resize(rows);
}

Vector::Vector(const std::vector<double> &initArr) {
    v = initArr;
    rows = v.size();
}

Vector Vector::clone() {
    Vector result(v);
    return result;
}

double& Vector::operator[](int row) {
    return v[row];
}

double Vector::at(int row) const {
    return v[row];
}

double Vector::operator[](int row) const {
    return at(row);
}

void Vector::swapRows(int r1, int r2) {
    if (r1 == r2) return;
    double tmp = v[r1];
    v[r1] = v[r2];
    v[r2] = tmp;
}

double Vector::norm() {
    double sum = 0;
    for (int i = 0; i < rows; i++)
    {
        double d = v[i];
        sum += d * d;
    }
    return sqrt(sum);
}

double Vector::norm(const Vector &weights) {
    double sum = 0;
    for (int i = 0; i < rows; i++)
    {
        double d = v[i] * weights[i];
        sum += d * d;
    }
    return sqrt(sum);
}

std::string Vector::toString() {
    std::string str = "[";
    bool first = true;
    for (double b : v) {
        if (!first) str +=",";
        str += std::to_string(b);
        first = false;
    }
    str += "]";
    return str;
}

Vector Vector::operator+(const Vector &other) {
    Vector result(rows);
    for (int i=0; i<rows; i++)
        result.v[i] = v[i]+other.v[i];
    return result;
}

Vector Vector::operator-(const Vector &other) {
    Vector result(rows);
    for (int i=0; i<rows; i++)
        result.v[i] = v[i]-other.v[i];
    return result;
}

void Vector::operator+=(const Vector &other)  {
    for (int i=0; i<rows; i++)
        v[i] += other.v[i];
}

void Vector::operator-=(const Vector &other)  {
     for (int i=0; i<rows; i++)
        v[i] -= other.v[i];
}