#ifndef SQUARE_MATRIX_H
#define SQUARE_MATRIX_H

#include "Matrix.h"
#include <cmath>
#include <stdexcept>

//квадратная матрица (наследник Matrix)
template <class T>
class SquareMatrix : public Matrix<T> {
public:
    //конструктор - только квадратные (size × size)
    SquareMatrix(int size) : Matrix<T>(size, size) {}

    //виртуальный деструктор
    virtual ~SquareMatrix() = default;

    //норма Фробениуса
    double Norm() const {
        double sum = 0.0;

        int size = this->GetRows();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                T value = this->Get(i, j);
                double absValue = static_cast<double>(value);
                sum += absValue * absValue;
            }
        }

        return std::sqrt(sum);
    }

    //✅ БЕЗ КОСТЫЛЯ: поменять указатели на строки
    void SwapRows(int row1, int row2) {
        int size = this->GetRows();

        if (row1 < 0 || row1 >= size || row2 < 0 || row2 >= size) {
            throw std::out_of_range("row index out of range");
        }

        //✅ ПРЯМОЙ доступ к rows (protected поле)
        MutableVector<T>* temp = this->rows->Get(row1);

        //✅ ИСПОЛЬЗУЕМ operator[] вместо Set()!
        (*this->rows)[row1] = this->rows->Get(row2);
        (*this->rows)[row2] = temp;
    }

    //умножить строку на скаляр
    void MultiplyRow(int row, const T& scalar) {
        int size = this->GetRows();

        if (row < 0 || row >= size) {
            throw std::out_of_range("row index out of range");
        }

        for (int j = 0; j < size; j++) {
            T value = this->Get(row, j);
            this->Set(row, j, value * scalar);
        }
    }

    //прибавить sourceRow * scalar к targetRow
    void AddRowToRow(int sourceRow, int targetRow, const T& scalar) {
        int size = this->GetRows();

        if (sourceRow < 0 || sourceRow >= size || targetRow < 0 || targetRow >= size) {
            throw std::out_of_range("row index out of range");
        }

        for (int j = 0; j < size; j++) {
            T sourceValue = this->Get(sourceRow, j);
            T targetValue = this->Get(targetRow, j);
            this->Set(targetRow, j, targetValue + sourceValue * scalar);
        }
    }

    //поменять два столбца местами
    void SwapCols(int col1, int col2) {
        int size = this->GetRows();

        if (col1 < 0 || col1 >= size || col2 < 0 || col2 >= size) {
            throw std::out_of_range("column index out of range");
        }

        for (int i = 0; i < size; i++) {
            T temp = this->Get(i, col1);
            this->Set(i, col1, this->Get(i, col2));
            this->Set(i, col2, temp);
        }
    }

    //умножить столбец на скаляр
    void MultiplyCol(int col, const T& scalar) {
        int size = this->GetRows();

        if (col < 0 || col >= size) {
            throw std::out_of_range("column index out of range");
        }

        for (int i = 0; i < size; i++) {
            T value = this->Get(i, col);
            this->Set(i, col, value * scalar);
        }
    }

    //прибавить sourceCol * scalar к targetCol
    void AddColToCol(int sourceCol, int targetCol, const T& scalar) {
        int size = this->GetRows();

        if (sourceCol < 0 || sourceCol >= size || targetCol < 0 || targetCol >= size) {
            throw std::out_of_range("column index out of range");
        }

        for (int i = 0; i < size; i++) {
            T sourceValue = this->Get(i, sourceCol);
            T targetValue = this->Get(i, targetCol);
            this->Set(i, targetCol, targetValue + sourceValue * scalar);
        }
    }

    //получить размер
    int GetSize() const {
        return this->GetRows();
    }
};

#endif