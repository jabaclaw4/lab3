#include <iostream>
#include <cmath>
#include "../src/MutableVector.h"
#include "../src/ImmutableVector.h"
#include "../src/Complex.h"
#include "../src/test_utils.h"

using namespace std;

void test_vector_creation() {
    //создание пустого вектора
    MutableVector<int>* v1 = new MutableVector<int>();
    check(v1->GetSize() == 0, "empty vector: size = 0");
    delete v1;

    //создание вектора заданного размера
    MutableVector<int>* v2 = new MutableVector<int>(5);
    check(v2->GetSize() == 5, "size 5: length = 5");
    check(v2->Get(0) == 0, "size 5: all zeros");
    delete v2;

    //создание из массива
    int arr[] = {1, 2, 3, 4, 5};
    MutableVector<int>* v3 = new MutableVector<int>(arr, 5);
    check(v3->GetSize() == 5, "from array: length = 5");
    check(v3->Get(0) == 1, "from array: first element");
    check(v3->Get(4) == 5, "from array: last element");
    delete v3;
}

void test_vector_addition() {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};

    MutableVector<int> v1(arr1, 3);
    MutableVector<int> v2(arr2, 3);

    Vector<int>* v3 = v1.Add(v2);

    check(v3->GetSize() == 3, "add: size = 3");
    check(v3->Get(0) == 5, "add: element 0 = 5");
    check(v3->Get(1) == 7, "add: element 1 = 7");
    check(v3->Get(2) == 9, "add: element 2 = 9");

    delete v3;
}

void test_vector_multiply_scalar() {
    int arr[] = {1, 2, 3};

    MutableVector<int> v1(arr, 3);
    Vector<int>* v2 = v1.MultiplyByScalar(2);

    check(v2->GetSize() == 3, "multiply: size = 3");
    check(v2->Get(0) == 2, "multiply: element 0 = 2");
    check(v2->Get(1) == 4, "multiply: element 1 = 4");
    check(v2->Get(2) == 6, "multiply: element 2 = 6");

    delete v2;
}

void test_vector_norm() {
    int arr[] = {3, 4};

    MutableVector<int> v(arr, 2);
    double norm = v.Norm();

    //сравнение с погрешностью для double
    check(std::abs(norm - 5.0) < 1e-9, "norm: 3-4-5 triangle = 5.0");
}

void test_vector_dot_product() {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};

    MutableVector<int> v1(arr1, 3);
    MutableVector<int> v2(arr2, 3);

    int dot = v1.DotProduct(v2);

    check(dot == 32, "dot product: 1*4 + 2*5 + 3*6 = 32");
}

void test_vector_double() {
    double arr[] = {1.5, 2.5, 3.5};

    MutableVector<double> v1(arr, 3);
    Vector<double>* v2 = v1.MultiplyByScalar(2.0);

    //сравнение с погрешностью
    check(std::abs(v2->Get(0) - 3.0) < 1e-9, "double: element 0 = 3.0");
    check(std::abs(v2->Get(1) - 5.0) < 1e-9, "double: element 1 = 5.0");
    check(std::abs(v2->Get(2) - 7.0) < 1e-9, "double: element 2 = 7.0");

    delete v2;
}

void test_vector_complex() {
    Complex c1(1, 2);
    Complex c2(3, 4);
    Complex arr[] = {c1, c2};

    MutableVector<Complex> v1(arr, 2);

    check(v1.GetSize() == 2, "complex: size = 2");
    check(v1.Get(0).GetReal() == 1, "complex: element 0 real = 1");
    check(v1.Get(0).GetImag() == 2, "complex: element 0 imag = 2");

    //умножение на скаляр
    Vector<Complex>* v2 = v1.MultiplyByScalar(Complex(2, 0));
    check(v2->Get(0).GetReal() == 2, "complex multiply: real = 2");
    check(v2->Get(0).GetImag() == 4, "complex multiply: imag = 4");

    delete v2;
}

void test_immutable_vector() {
    int arr[] = {1, 2, 3};

    ImmutableVector<int> v1(arr, 3);
    Vector<int>* v2 = v1.Add(v1);

    check(v1.Get(0) == 1, "immutable: original unchanged");
    check(v2->Get(0) == 2, "immutable: new vector = 2");

    delete v2;
}

void test_vector_operators() {
    int arr[] = {1, 2, 3};

    MutableVector<int> v(arr, 3);

    //оператор []
    check(v[0] == 1, "operator[]: index 0 = 1");
    check(v[2] == 3, "operator[]: index 2 = 3");
}

void test_vector_errors() {
    MutableVector<int> v(3);

    //индекс за границами
    bool caught = false;
    try {
        v.Get(10);
    } catch (...) {
        caught = true;
    }
    check(caught, "exception: index out of range");

    //разные размеры
    int arr[] = {1, 2};
    MutableVector<int> v2(arr, 2);

    caught = false;
    try {
        v.Add(v2);
    } catch (...) {
        caught = true;
    }
    check(caught, "exception: different sizes");
}

void run_test_vector() {
    reset_counters();

    cout << "=== Vector Tests ===" << endl;

    test_vector_creation();
    test_vector_addition();
    test_vector_multiply_scalar();
    test_vector_norm();
    test_vector_dot_product();
    test_vector_double();
    test_vector_complex();
    test_immutable_vector();
    test_vector_operators();
    test_vector_errors();

    print_results();
}