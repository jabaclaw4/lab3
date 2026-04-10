#ifndef VECTOR_BASE_H
#define VECTOR_BASE_H

#include <cmath>
#include <stdexcept>
#include "Vector.h"
#include "Sequence.h"
#include "Complex.h"
#include <type_traits>
#include "ResultInfo.h"
#include <iostream>

//базовая реализация вектора
template <class T>
class VectorBase : public Vector<T> {
protected:
    Sequence<T>* data;

    virtual VectorBase<T>* CreateNew() const = 0;
    virtual VectorBase<T>* CreateNew(int size) const = 0;

    //добавь getter для data (чтобы можно было вывести)
    const Sequence<T>* GetData() const {
        return this->data;
    }

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

    friend std::ostream& operator<<(std::ostream& os, const VectorBase<T>& vec) {
        if (vec.data != nullptr) {
            os << *vec.data;
        } else {
            os << "[]";
        }
        return os;
    }


private:
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

#endif