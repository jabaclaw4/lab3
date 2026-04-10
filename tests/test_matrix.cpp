#include <iostream>
#include "../src/Matrix.h"
#include "../src/test_utils.h"

using namespace std;

void test_matrix_creation() {
    Matrix<int> m(2, 3);  //2 строки, 3 столбца

    check(m.GetRows() == 2, "matrix: rows = 2");
    check(m.GetCols() == 3, "matrix: cols = 3");
    check(m.Get(0, 0) == 0, "matrix: element [0][0] = 0");
}

void test_matrix_set_get() {
    Matrix<int> m(2, 2);

    m.Set(0, 0, 1);
    m.Set(0, 1, 2);
    m.Set(1, 0, 3);
    m.Set(1, 1, 4);

    check(m.Get(0, 0) == 1, "matrix: [0][0] = 1");
    check(m.Get(0, 1) == 2, "matrix: [0][1] = 2");
    check(m.Get(1, 0) == 3, "matrix: [1][0] = 3");
    check(m.Get(1, 1) == 4, "matrix: [1][1] = 4");
}

void test_matrix_add() {
    Matrix<int> m1(2, 2);
    m1.Set(0, 0, 1); m1.Set(0, 1, 2);
    m1.Set(1, 0, 3); m1.Set(1, 1, 4);

    Matrix<int> m2(2, 2);
    m2.Set(0, 0, 5); m2.Set(0, 1, 6);
    m2.Set(1, 0, 7); m2.Set(1, 1, 8);

    Matrix<int>* result = m1.Add(m2);

    check(result->Get(0, 0) == 6, "matrix add: [0][0] = 6");
    check(result->Get(0, 1) == 8, "matrix add: [0][1] = 8");
    check(result->Get(1, 0) == 10, "matrix add: [1][0] = 10");
    check(result->Get(1, 1) == 12, "matrix add: [1][1] = 12");

    delete result;
}

void run_test_matrix() {
    reset_counters();

    cout << "=== Matrix Tests ===" << endl;

    test_matrix_creation();
    test_matrix_set_get();
    test_matrix_add();

    print_results();
}