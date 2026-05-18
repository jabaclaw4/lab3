#ifndef COMPLEX_H
#define COMPLEX_H

#include <cmath>
#include <stdexcept>
#include <iosfwd>

class Complex {
private:
    double real;
    double imag; //мнимая часть

public:
    //конструктор по умолчанию (0 + 0i)
    Complex() : real(0.0), imag(0.0) {}

    //конструктор с параметрами
    Complex(double real, double imag = 0.0) : real(real), imag(imag) {}

    //копирующий конструктор
    Complex(const Complex& other) : real(other.real), imag(other.imag) {}

    //получить действительную часть
    double GetReal() const {
        return this->real;
    }

    //получить мнимую часть
    double GetImag() const {
        return this->imag;
    }

    //модуль комплексного числа: |a + bi| = sqrt(a² + b²)
    double Abs() const {
        return std::sqrt(this->real * this->real + this->imag * this->imag);
    }

    //сложение: (a + bi) + (c + di) = (a+c) + (b+d)i
    Complex operator+(const Complex& other) const {
        return Complex(this->real + other.real, this->imag + other.imag);
    }

    //вычитание: (a + bi) - (c + di) = (a-c) + (b-d)i
    Complex operator-(const Complex& other) const {
        return Complex(this->real - other.real, this->imag - other.imag);
    }

    //умножение: (a + bi) * (c + di) = (ac - bd) + (ad + bc)i
    Complex operator*(const Complex& other) const {
        double newReal = this->real * other.real - this->imag * other.imag;
        double newImag = this->real * other.imag + this->imag * other.real;
        return Complex(newReal, newImag);
    }

    //умножение на вещественное число: (a + bi) * k = (ak) + (bk)i
    Complex operator*(double scalar) const {
        return Complex(this->real * scalar, this->imag * scalar);
    }

    //умножение на вещественное число (k * (a + bi))
    friend Complex operator*(double scalar, const Complex& c) {
        return c * scalar;
    }

    //деление: (a + bi) / (c + di) = ((ac + bd) + (bc - ad)i) / (c² + d²)
    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;

        if (denominator == 0.0) {
            throw std::runtime_error("division by zero");
        }

        double newReal = (this->real * other.real + this->imag * other.imag) / denominator;
        double newImag = (this->imag * other.real - this->real * other.imag) / denominator;

        return Complex(newReal, newImag);
    }

    //сравнение (по модулю)
    bool operator==(const Complex& other) const {
        return (this->real == other.real) && (this->imag == other.imag);
    }

    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    //оператор присваивания
    Complex& operator=(const Complex& other) {
        if (this != &other) {
            this->real = other.real;
            this->imag = other.imag;
        }
        return *this;
    }
};

#endif