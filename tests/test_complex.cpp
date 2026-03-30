#include <iostream>
#include "../src/Complex.h"
#include "../src/test_utils.h"

using namespace std;

void run_test_complex() {
    reset_counters();

    cout << "=== Complex Tests ===" << endl;

    //создание
    Complex c1(3, 4);  // 3 + 4i
    check(c1.GetReal() == 3, "creation: real = 3");
    check(c1.GetImag() == 4, "creation: imag = 4");

    //модуль
    double abs = c1.Abs();  // sqrt(3² + 4²) = 5
    check(abs == 5.0, "abs: 3-4-5 triangle = 5.0");

    //сложение
    Complex c2(1, 2);  // 1 + 2i
    Complex c3 = c1 + c2;  // (3+1) + (4+2)i = 4 + 6i
    check(c3.GetReal() == 4, "add: real = 4");
    check(c3.GetImag() == 6, "add: imag = 6");

    //вычитание
    Complex c4 = c1 - c2;  // (3-1) + (4-2)i = 2 + 2i
    check(c4.GetReal() == 2, "sub: real = 2");
    check(c4.GetImag() == 2, "sub: imag = 2");

    //умножение
    Complex c5 = c1 * c2;  // (3*1 - 4*2) + (3*2 + 4*1)i = -5 + 10i
    check(c5.GetReal() == -5, "mul: real = -5");
    check(c5.GetImag() == 10, "mul: imag = 10");

    //умножение на скаляр
    Complex c6 = c1 * 2.0;  // 6 + 8i
    check(c6.GetReal() == 6, "mul scalar: real = 6");
    check(c6.GetImag() == 8, "mul scalar: imag = 8");

    print_results();
}