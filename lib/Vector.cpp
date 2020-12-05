#include "Vector.h"

Vector::Vector(int rows):rows(rows) {
    v.resize(rows);
}

Vector::Vector(const std::vector<float_type> &initArr) {
    v = initArr;
    rows = v.size();
}

Vector Vector::clone() {
    Vector result(v);
    return result;
}

float_type& Vector::operator[](int row) {
    return v[row];
}

float_type Vector::at(int row) const {
    return v[row];
}

float_type Vector::operator[](int row) const {
    return at(row);
}

void Vector::swapRows(int r1, int r2) {
    if (r1 == r2) return;
    float_type tmp = v[r1];
    v[r1] = v[r2];
    v[r2] = tmp;
}

float_type Vector::norm() {
    float_type sum = 0;
    for (int i = 0; i < rows; i++)
    {
        float_type d = v[i];
        sum += d * d;
    }
    return sqrt(sum);
}

float_type Vector::norm(const Vector &weights) {
    float_type sum = 0;
    for (int i = 0; i < rows; i++)
    {
        float_type d = v[i] * weights[i];
        sum += d * d;
    }
    return sqrt(sum);
}

std::string Vector::toString() {
    std::string str = "[";
    bool first = true;
    for (float_type b : v) {
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