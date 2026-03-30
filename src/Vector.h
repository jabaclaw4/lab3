#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include "ResultInfo.h"  //✅ ДОБАВИЛИ!

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

    //✅ ДОБАВЛЕНО: безопасное получение элемента (монада)
    virtual ResultInfo<T> TryGet(int index) const = 0;

    //ОПЕРАЦИИ С ВЕКТОРАМИ

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

    //оператор << для вывода
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