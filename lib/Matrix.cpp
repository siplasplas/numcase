#include "Matrix.h"
#include <cmath>
#include <cassert>

Matrix::Matrix(int rows, int cols):rows(rows),cols(cols) {
    v.resize(rows*cols);
}

Matrix::Matrix(int rows, int cols, const std::vector<double> &initArr)
                        :rows(rows),cols(cols) {
    if (initArr.size()!=rows*cols) throw std::exception();
    v = initArr;
}

double& Matrix::at(int row, int col) {
    return v[row * cols + col];
}

double Matrix::at(int row, int col) const{
    return v[row * cols + col];
}

Matrix Matrix::operator+(const Matrix &other) {
    Matrix result(rows, cols);
    for (int i=0; i<rows*cols; i++)
        result.v[i] = v[i]+other.v[i];
    return result;
}

Matrix Matrix::operator-(const Matrix &other) {
    Matrix result(rows, cols);
    for (int i=0; i<rows*cols; i++)
        result.v[i] = v[i]-other.v[i];
    return result;
}

Vector Matrix::operator*(const Vector &vec) {
    if (cols != vec.getRows()) throw new std::exception();
    Vector v(rows);
    for (int i = 0; i < rows; i++)
    {
        double sum = 0;
        for (int j = 0; j < vec.getRows(); j++)
            sum += at(i, j) * vec[j];
        v[i] = sum;
    }
    return v;
}

void Matrix::SwapRows(int r1, int r2, int start) {
    if (r1 == r2) return;
    int firstR1 = r1 * cols;
    int firstR2 = r2 * cols;
    for (int i = start; i < cols; i++)
    {
        if (fabs(v[firstR1 + i])<1e-8 && fabs(v[firstR2 + i])<1e-8)
            printf("bezuzyteczne %d<->%d %d\n",r1,r2,start);
        double tmp = v[firstR1 + i];
        v[firstR1 + i] = v[firstR2 + i];
        v[firstR2 + i] = tmp;
    }
}

void Matrix::SwapCols(int cdiag, int cmax) {
    if (cdiag == cmax) return;
    for (int i = 0; i < rows; i++)
    {
        double tmp = v[cdiag + i * cols];
        v[cdiag + i * cols] = v[cmax + i * cols];
        v[cmax + i * cols] = tmp;
    }
    assert(swap[cdiag]==0);
    swap[cdiag] = cmax;
}

//with partial pivot
void Matrix::ElimPartial(Vector &B) {
    for (int diag = 0; diag < rows; diag++)
    {
        int max_row = diag;
        double max_val = fabs(at(diag, diag));
        double d;
        for (int row = diag + 1; row < rows; row++)
            if ((d = fabs(at(row, diag))) > max_val)
            {
                max_row = row;
                max_val = d;
            }
        SwapRows(diag, max_row, diag);
        B.swapRows(diag, max_row);
        double invd = 1 / at(diag, diag);
        for (int col = diag; col < cols; col++)
            at(diag, col) *= invd;
        B[diag] *= invd;
        for (int row = 0; row < rows; row++)
        {
            d = at(row, diag);
            if (row != diag)
            {
                for (int col = diag; col < cols; col++)
                    at(row, col) -= d * at(diag, col);
                B[row] -= d * B[diag];
            }
        }
    }
}

//with complete pivot
void Matrix::ElimComplete(Vector &B) {
    swap.clear();
    swap.resize(cols);
    for (int diag = 0; diag < rows; diag++)
    {
        int max_row = diag;
        int max_col = diag;
        double max_val = fabs(at(diag, diag));
        double d;
        for (int row = diag; row < rows; row++)
            for (int col = diag; col < cols; col++)
                if ((d = fabs(at(row, col))) > max_val)
                {
                    max_row = row;
                    max_col = col;
                    max_val = d;
                }
        SwapRows(diag, max_row, diag);
        B.swapRows(diag, max_row);
        SwapCols(diag,max_col);
        double invd = 1 / at(diag, diag);
        for (int col = diag; col < cols; col++)
            at(diag, col) *= invd;
        B[diag] *= invd;
        for (int row = 0; row < rows; row++)
        {
            d = at(row, diag);
            if (row != diag)
            {
                for (int col = diag; col < cols; col++)
                    at(row, col) -= d * at(diag, col);
                B[row] -= d * B[diag];
            }
        }
    }
    for (int i=swap.size()-1; i>=0; i--) {
        if (swap[i]!=0)
            B.swapRows(i,swap[i]);
    }
}

Matrix Matrix::transposedMult(const Matrix &B) {
    if (rows != B.rows)
        throw new std::exception();
    Matrix R(cols, B.cols);
    for (int row = 0; row < cols; row++)
        for (int col = 0; col < B.cols; col++)
        {
            double sum = 0;
            for (int k = 0; k < rows; k++)
                sum += at(k, row) * B.at(k, col);
            R.at(row,col)= sum;
        }
    return R;
}

Vector Matrix::transposedMult(const Vector &Y) {
    if (rows != Y.getRows())
        throw new std::exception();
    Vector R(cols);
    for (int row = 0; row < cols; row++)
    {
        double sum = 0;
        for (int k = 0; k < rows; k++)
            sum += at(k,row) * Y[k];
        R[row] = sum;
    }
    return R;
}

std::string Matrix::toString() {
    std::string str = "[";
    for (int i=0; i<rows*cols; i++)
    {
        double b = v[i];
        if (i % cols != 0) str +=",";
        str += std::to_string(b);
        if (i<rows*cols-1 && i % cols == cols-1) str += "\n ";
    }
    str += "]";
    return str;
}


