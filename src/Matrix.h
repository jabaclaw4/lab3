#ifndef MATRIX_H
#define MATRIX_H

#include "DynamicArray.h"
#include <stdexcept>
#include <iosfwd>

template <class T> class Matrix;
template <class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix);

//матрица на базе DynamicArray<DynamicArray<T>*>
template <class T>
class Matrix {
protected://protected чтобы наследники могли использовать
    DynamicArray<DynamicArray<T>*>* rows;  //массив указателей на строки
    int numRows;
    int numCols;

public:
    Matrix(int rows, int cols) : numRows(rows), numCols(cols) {
        if (rows <= 0 || cols <= 0) {
            throw std::invalid_argument("matrix dimensions must be positive");
        }

        //создаём массив указателей на строки
        this->rows = new DynamicArray<DynamicArray<T>*>(rows);

        //создаём каждую строку
        for (int i = 0; i < rows; i++) {
            DynamicArray<T>* row = new DynamicArray<T>(cols);
            //инициализируем нулями
            for (int j = 0; j < cols; j++) {
                row->Set(j, T());  //T() = 0 для int/double
            }
            this->rows->Set(i, row);
        }
    }

    //виртуальный деструктор
    virtual ~Matrix() {
        //удаляем каждую строку
        for (int i = 0; i < numRows; i++) {
            delete this->rows->Get(i);
        }
        delete this->rows;
    }

    //получить элемент
    virtual T Get(int row, int col) const {
        if (row < 0 || row >= numRows || col < 0 || col >= numCols) {
            throw std::out_of_range("matrix index out of range");
        }

        return this->rows->Get(row)->Get(col);
    }

    //установить элемент
    virtual void Set(int row, int col, const T& value) {
        if (row < 0 || row >= numRows || col < 0 || col >= numCols) {
            throw std::out_of_range("matrix index out of range");
        }

        this->rows->Get(row)->Set(col, value);
    }

    //сложение матриц
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

    //объявление дружественного оператора а определениев PrintUtils.h
    friend std::ostream& operator<< <>(std::ostream& os, const Matrix<T>& matrix);

    int GetRows() const { return numRows; }
    int GetCols() const { return numCols; }
};

#endif