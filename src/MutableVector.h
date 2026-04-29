#ifndef MUTABLE_VECTOR_H
#define MUTABLE_VECTOR_H

#include "VectorBase.h"
#include "MutableArraySequence.h"

//изменяемый вектор
template <class T>
class MutableVector : public VectorBase<T> {
protected:
    //создать новый экземпляр (пустой)
    VectorBase<T>* CreateNew() const override {
        return new MutableVector<T>();
    }

    //создать новый экземпляр (заданного размера)
    VectorBase<T>* CreateNew(int size) const override {
        MutableVector<T>* vec = new MutableVector<T>();
        vec->data = new MutableArraySequence<T>();
        return vec;
    }

public:
    //конструктор по умолчанию
    MutableVector() {
        this->data = new MutableArraySequence<T>();
    }

    //создать вектор заданного размера (все элементы = 0)
    MutableVector(int size) {
        if (size < 0) {
            throw std::invalid_argument("size cannot be negative");
        }

        this->data = new MutableArraySequence<T>();

        //заполняем нулями
        for (int i = 0; i < size; i++) {
            this->data = this->data->Append(T());
        }
    }

    //создать вектор из массива
    MutableVector(T* items, int count) {
        if (count < 0) {
            throw std::invalid_argument("count cannot be negative");
        }
        if (items == nullptr && count > 0) {
            throw std::invalid_argument("items is null");
        }

        this->data = new MutableArraySequence<T>(items, count);
    }

    //копирующий конструктор
    MutableVector(const MutableVector<T>& other) {
        this->data = new MutableArraySequence<T>();

        for (int i = 0; i < other.GetSize(); i++) {
            this->data = this->data->Append(other.Get(i));
        }
    }

    MutableVector& operator=(const MutableVector<T>& other) {
        if (this == &other) {
            return *this;
        }

        //удаляем старые данные
        delete this->data;

        //копируем из other
        this->data = new MutableArraySequence<T>();

        for (int i = 0; i < other.GetSize(); i++) {
            this->data = this->data->Append(other.Get(i));
        }

        return *this;
    }

    //установить элемент по индексу
    void Set(int index, const T& value) {
        if (index < 0 || index >= this->GetSize()) {
            throw std::out_of_range("index out of range");
        }

        //пересоздаём последовательность с новым значением
        Sequence<T>* newData = new MutableArraySequence<T>();

        for (int i = 0; i < this->GetSize(); i++) {
            if (i == index) {
                newData = newData->Append(value);
            } else {
                newData = newData->Append(this->data->Get(i));
            }
        }

        delete this->data;
        this->data = newData;
    }

    MutableVector<T>& operator+=(const Vector<T>& other) {
        if (this->GetSize() != other.GetSize()) {
            throw std::invalid_argument("vectors must have same size");
        }

        for (int i = 0; i < this->GetSize(); i++) {
            T val = this->Get(i) + other.Get(i);
            this->Set(i, val);
        }

        return *this;
    }

    MutableVector<T>& operator-=(const Vector<T>& other) {
        if (this->GetSize() != other.GetSize()) {
            throw std::invalid_argument("vectors must have same size");
        }

        for (int i = 0; i < this->GetSize(); i++) {
            T val = this->Get(i) - other.Get(i);
            this->Set(i, val);
        }

        return *this;
    }

    MutableVector<T>& operator*=(const T& scalar) {
        for (int i = 0; i < this->GetSize(); i++) {
            T val = this->Get(i) * scalar;
            this->Set(i, val);
        }

        return *this;
    }
};

#endif