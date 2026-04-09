#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include "ResultInfo.h"
#include "VectorBase.h"

//базовый интерфейс для векторов
template <class T>
class Vector {
public:
    //деструктор
    virtual ~Vector() = default;

    //получить элемент по индексу
    virtual T Get(int index) const = 0;

    //получить размер вектора
    virtual int GetSize() const = 0;

    virtual ResultInfo<T> TryGet(int index) const = 0;

    //сложение векторов: v1 + v2
    virtual Vector<T>* Add(const Vector<T>& other) const = 0;

    //умножение на скаляр: k * v
    virtual Vector<T>* MultiplyByScalar(const T& scalar) const = 0;

    //норма вектора (длина): ||v||
    virtual double Norm() const = 0;

    //скалярное произведение: v1 · v2
    virtual T DotProduct(const Vector<T>& other) const = 0;

    //оператор [] для доступа
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
        return vec * scalar;//доступ к закрытым полям
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

};

#endif