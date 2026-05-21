#ifndef VECTOR_BASE_H
#define VECTOR_BASE_H

#include <cmath>
#include <stdexcept>
#include "Vector.h"
#include "Sequence.h"
#include "Complex.h"
#include <type_traits>
#include "ResultInfo.h"

//базовая реализация вектора
template <class T>
class VectorBase : public Vector<T> {
protected:
    Sequence<T>* data;

    virtual VectorBase<T>* CreateNew() const = 0;
    virtual VectorBase<T>* CreateNew(int size) const = 0;

public:
    VectorBase() : data(nullptr) {}

    virtual ~VectorBase() {
        if (this->data != nullptr) {
            delete this->data;
        }
    }

    //получить элемент по индексу
    T Get(int index) const override {
        if (index < 0 || index >= this->GetSize()) {
            throw std::out_of_range("index out of range");
        }

        return this->data->Get(index);
    }
//монада
    ResultInfo<T> TryGet(int index) const override {
        if (index < 0 || index >= this->GetSize()) {
            return ResultInfo<T>::Failure("index out of range");
        }

        return ResultInfo<T>::Success(this->data->Get(index));
    }

    int GetSize() const override {
        if (this->data == nullptr) {
            return 0;
        }
        return this->data->GetLength();
    }

    Vector<T>* Add(const Vector<T>& other) const override {
        if (this->GetSize() != other.GetSize()) {
            throw std::invalid_argument("vectors must have same size");
        }

        VectorBase<T>* result = this->CreateNew(this->GetSize());

        for (int i = 0; i < this->GetSize(); i++) {
            T sum = this->Get(i) + other.Get(i);
            result->data = result->data->Append(sum);
        }

        return result;
    }

    Vector<T>* MultiplyByScalar(const T& scalar) const override {
        VectorBase<T>* result = this->CreateNew(this->GetSize());

        for (int i = 0; i < this->GetSize(); i++) {
            T product = this->Get(i) * scalar;
            result->data = result->data->Append(product);
        }

        return result;
    }

    double Norm() const override {
        double sum = 0.0;

        for (int i = 0; i < this->GetSize(); i++) {
            T value = this->Get(i);
            double absValue = NormHelper(value);
            sum += absValue * absValue;
        }

        return std::sqrt(sum);
    }


    T DotProduct(const Vector<T>& other) const override {
        if (this->GetSize() != other.GetSize()) {
            throw std::invalid_argument("vectors must have same size");
        }

        T sum = T();

        for (int i = 0; i < this->GetSize(); i++) {
            sum = sum + (this->Get(i) * other.Get(i));
        }

        return sum;
    }

    template <class Func>
    Vector<T>* Map(Func f) const;

    template <class Predicate>
    Vector<T>* Where(Predicate pred) const;

    template <class Func>
    T Reduce(Func f, T initial) const;


private:
    template <typename U>
    static double NormHelper(const U& value) {
        if constexpr (std::is_same_v<U, Complex>) {//проверрка во время компиляции это специализация по другому не получается
            //потому что нельзя переопределять методы класса вне самого класса
            //для Complex
            return value.Abs();
        } else {
            //для int, double и остальных
            return static_cast<double>(value);
        }
    }
};

template <class T>
template <class Func>
Vector<T>* VectorBase<T>::Map(Func f) const {
    Sequence<T>* newData = this->data->Map(f);

    VectorBase<T>* result = this->CreateNew();
    result->data = newData;

    return result;
}

template <class T>
template <class Predicate>
Vector<T>* VectorBase<T>::Where(Predicate pred) const {
    Sequence<T>* newData = this->data->Where(pred);

    VectorBase<T>* result = this->CreateNew();
    result->data = newData;

    return result;
}

template <class T>
template <class Func>
T VectorBase<T>::Reduce(Func f, T initial) const {
    return this->data->Reduce(f, initial);
}

#endif