#pragma once
#include "Vector.h"

class Matrix {
    std::vector<double> v;
    int rows;
    int cols;
    std::vector<int> swap;
public:
    Matrix(int rows, int cols);
    Matrix(int rows, int cols, const std::vector<double> &initArr);
    double& at(int row, int col);
    double at(int row, int col) const;
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