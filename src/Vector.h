#ifndef VECTOR_H
#define VECTOR_H

#include "ResultInfo.h"
#include <iostream>

template <class T>
class Vector {
public:
    virtual ~Vector() = default;

    virtual T Get(int index) const = 0;
    virtual int GetSize() const = 0;
    virtual ResultInfo<T> TryGet(int index) const = 0;

    virtual Vector<T>* Add(const Vector<T>& other) const = 0;
    virtual Vector<T>* MultiplyByScalar(const T& scalar) const = 0;
    virtual double Norm() const = 0;
    virtual T DotProduct(const Vector<T>& other) const = 0;

    //операторы
    T operator[](int index) const {
        return this->Get(index);
    }

    Vector<T>* operator+(const Vector<T>& other) const {
        return this->Add(other);
    }

    Vector<T>* operator*(const T& scalar) const {
        return this->MultiplyByScalar(scalar);
    }

    friend Vector<T>* operator*(const T& scalar, const Vector<T>& vec) {
        return vec * scalar;
    }

    bool operator==(const Vector<T>& other) const {
        if (this->GetSize() != other.GetSize()) {
            return false;
        }

        for (int i = 0; i < this->GetSize(); i++) {
            if (this->Get(i) != other.Get(i)) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Vector<T>& other) const {
        return !(*this == other);
    }

    //✅ operator<< ИСПОЛЬЗУЕТ ТОЛЬКО ПУБЛИЧНЫЙ ИНТЕРФЕЙС
    friend std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
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
};

#endif