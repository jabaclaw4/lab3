#ifndef PRINT_UTILS_H
#define PRINT_UTILS_H

#include <iostream>
#include "Complex.h"
#include "Matrix.h"
#include "Vector.h"

inline std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.GetReal();

    if (c.GetImag() >= 0) {
        os << " + " << c.GetImag() << "i";
    } else {
        os << " - " << (-c.GetImag()) << "i";
    }

    return os;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
    os << "[";

    for (int i = 0; i < matrix.GetRows(); i++) {
        if (i > 0) {
            os << " ";
        }

        os << "[";
        for (int j = 0; j < matrix.GetCols(); j++) {
            os << matrix.Get(i, j);
            if (j < matrix.GetCols() - 1) {
                os << ", ";
            }
        }
        os << "]";

        if (i < matrix.GetRows() - 1) {
            os << std::endl;
        }
    }

    os << "]";
    return os;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
    os << "[";
    for (int i = 0; i < vec.GetSize(); i++) {
        os << vec.Get(i);
        if (i < vec.GetSize() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

#endif