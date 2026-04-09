#ifndef MATRIX_H
#define MATRIX_H

#include "MutableVector.h"
#include <stdexcept>
#include <iostream>

//матрица на базе Vector<Vector<T>*> (вектор указателей на векторы)
template <class T>
class Matrix {
protected:  //чтобы наследники могли использовать
    MutableVector<MutableVector<T>*>* rows; //указатель на вектор указателей на векторы элементов T
    int numRows;
    int numCols;

public:
    //создать матрицу размером rows x cols
    Matrix(int rows, int cols) : numRows(rows), numCols(cols) {
        if (rows <= 0 || cols <= 0) {
            throw std::invalid_argument("matrix dimensions must be positive");
        }

        //создаём вектор указателей на строки
        this->rows = new MutableVector<MutableVector<T>*>(rows);

        //создаём каждую строку
        for (int i = 0; i < rows; i++) {
            MutableVector<T>* row = new MutableVector<T>(cols);
            this->rows->Set(i, row);
        }
    }

    virtual ~Matrix() {
        //удаляем каждую строку
        for (int i = 0; i < numRows; i++) {
            delete this->rows->Get(i);
        }
        delete this->rows;
    }

    virtual T Get(int row, int col) const {
        if (row < 0 || row >= numRows || col < 0 || col >= numCols) {
            throw std::out_of_range("matrix index out of range");
        }

        return this->rows->Get(row)->Get(col);
    }

    virtual void Set(int row, int col, const T& value) {
        if (row < 0 || row >= numRows || col < 0 || col >= numCols) {
            throw std::out_of_range("matrix index out of range");
        }

        this->rows->Get(row)->Set(col, value);
    }

    //виртуальное сложение
    virtual Matrix<T>* Add(const Matrix<T>& other) const {
        if (this->numRows != other.numRows || this->numCols != other.numCols) {
            throw std::invalid_argument("matrices must have same dimensions");
        }

        Matrix<T>* result = new Matrix<T>(numRows, numCols);

        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                T sum = this->Get(i, j) + other.Get(i, j);
                result->Set(i, j, sum);
            }
        }

        return result;
    }

    //умножение на скаляр
    virtual Matrix<T>* MultiplyByScalar(const T& scalar) const {
        Matrix<T>* result = new Matrix<T>(numRows, numCols);

        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                T product = this->Get(i, j) * scalar;
                result->Set(i, j, product);
            }
        }

        return result;
    }

    //вывод
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
        os << "[" << std::endl;
        for (int i = 0; i < matrix.numRows; i++) {
            os << "  " << *(matrix.rows->Get(i)) << std::endl;
        }
        os << "]";
        return os;
    }

    int GetRows() const { return numRows; }
    int GetCols() const { return numCols; }
};

#endif