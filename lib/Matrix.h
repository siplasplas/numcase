#pragma once
#include "Vector.h"

class Matrix {
    std::vector<float_type> v;
    int rows;
    int cols;
    std::vector<int> swap;
public:
    Matrix(int rows, int cols);
    Matrix(int rows, int cols, const std::vector<float_type> &initArr);
    float_type& at(int row, int col);
    float_type at(int row, int col) const;
    Matrix operator+(const Matrix &other);
    Matrix operator-(const Matrix &other);
    Vector operator*(const Vector &vec);
    Matrix operator*(const Matrix &other);
    void SwapRows(int r1, int r2, int start=0);
    void SwapCols(int cdiag, int cmax);
    void ElimPartial(Vector &B);
    void ElimComplete(Vector &B);
    Matrix transposedMult(const Matrix &B);
    Vector transposedMult(const Vector &Y);
    std::string toString();
};