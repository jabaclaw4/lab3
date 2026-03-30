#ifndef IMMUTABLE_VECTOR_H
#define IMMUTABLE_VECTOR_H

#include "VectorBase.h"
#include "ImmutableArraySequence.h"

//неизменяемый вектор (операции возвращают новый вектор)
template <class T>
class ImmutableVector : public VectorBase<T> {
protected:
    //создать новый экземпляр (пустой)
    VectorBase<T>* CreateNew() const override {
        return new ImmutableVector<T>();
    }

    //создать новый экземпляр (заданного размера)
    VectorBase<T>* CreateNew(int size) const override {
        ImmutableVector<T>* vec = new ImmutableVector<T>();
        vec->data = new ImmutableArraySequence<T>();
        return vec;
    }

public:
    //конструктор по умолчанию
    ImmutableVector() {
        this->data = new ImmutableArraySequence<T>();
    }

    //создать вектор заданного размера (все элементы = 0)
    ImmutableVector(int size) {
        if (size < 0) {
            throw std::invalid_argument("size cannot be negative");
        }

        Sequence<T>* seq = new ImmutableArraySequence<T>();

        //заполняем нулями
        for (int i = 0; i < size; i++) {
            Sequence<T>* old = seq;
            seq = seq->Append(T());
            delete old;
        }

        this->data = seq;
    }

    //создать вектор из массива
    ImmutableVector(T* items, int count) {
        if (count < 0) {
            throw std::invalid_argument("count cannot be negative");
        }
        if (items == nullptr && count > 0) {
            throw std::invalid_argument("items is null");
        }

        this->data = new ImmutableArraySequence<T>(items, count);
    }

    //копирующий конструктор
    ImmutableVector(const ImmutableVector<T>& other) {
        Sequence<T>* seq = new ImmutableArraySequence<T>();

        for (int i = 0; i < other.GetSize(); i++) {
            Sequence<T>* old = seq;
            seq = seq->Append(other.Get(i));
            delete old;
        }

        this->data = seq;
    }
};

#endif
