#include <iostream>
#include <cmath>  //✅ ДОБАВЬ для fabs
#include "../src/SquareMatrix.h"
#include "../src/test_utils.h"  //✅ ИСПРАВЛЕНО: без ../src/

using namespace std;

void test_square_matrix_creation() {
    SquareMatrix<int> m(3);

    check(m.GetSize() == 3, "square matrix: size = 3");
    check(m.GetRows() == 3, "square matrix: rows = 3");
    check(m.GetCols() == 3, "square matrix: cols = 3");
    check(m.Get(0, 0) == 0, "square matrix: element [0][0] = 0");
}

void test_square_matrix_set_get() {
    SquareMatrix<int> m(3);

    m.Set(0, 0, 1);
    m.Set(0, 1, 2);
    m.Set(0, 2, 3);
    m.Set(1, 0, 4);
    m.Set(1, 1, 5);
    m.Set(1, 2, 6);
    m.Set(2, 0, 7);
    m.Set(2, 1, 8);
    m.Set(2, 2, 9);

    check(m.Get(0, 0) == 1, "square matrix: [0][0] = 1");
    check(m.Get(1, 1) == 5, "square matrix: [1][1] = 5");
    check(m.Get(2, 2) == 9, "square matrix: [2][2] = 9");
}

void test_square_matrix_norm() {
    SquareMatrix<int> m(2);
    m.Set(0, 0, 3);  // 3² = 9
    m.Set(0, 1, 4);  // 4² = 16
    m.Set(1, 0, 0);  // 0² = 0
    m.Set(1, 1, 0);  // 0² = 0

    //норма = sqrt(9 + 16) = sqrt(25) = 5
    double norm = m.Norm();
    check(fabs(norm - 5.0) < 0.001, "square matrix: norm = 5");  //✅ ИСПРАВЛЕНО
}

void test_square_matrix_swap_rows() {
    SquareMatrix<int> m(3);

    //строка 0: [1, 2, 3]
    m.Set(0, 0, 1); m.Set(0, 1, 2); m.Set(0, 2, 3);

    //строка 1: [4, 5, 6]
    m.Set(1, 0, 4); m.Set(1, 1, 5); m.Set(1, 2, 6);

    //строка 2: [7, 8, 9]
    m.Set(2, 0, 7); m.Set(2, 1, 8); m.Set(2, 2, 9);

    //меняем строки 0 и 2
    m.SwapRows(0, 2);

    //теперь строка 0 = [7, 8, 9]
    check(m.Get(0, 0) == 7, "swap rows: [0][0] = 7");
    check(m.Get(0, 1) == 8, "swap rows: [0][1] = 8");
    check(m.Get(0, 2) == 9, "swap rows: [0][2] = 9");

    //строка 2 = [1, 2, 3]
    check(m.Get(2, 0) == 1, "swap rows: [2][0] = 1");
    check(m.Get(2, 1) == 2, "swap rows: [2][1] = 2");
    check(m.Get(2, 2) == 3, "swap rows: [2][2] = 3");
}

void test_square_matrix_multiply_row() {
    SquareMatrix<int> m(2);
    m.Set(0, 0, 1); m.Set(0, 1, 2);
    m.Set(1, 0, 3); m.Set(1, 1, 4);

    //умножаем строку 0 на 3
    m.MultiplyRow(0, 3);

    check(m.Get(0, 0) == 3, "multiply row: [0][0] = 3");
    check(m.Get(0, 1) == 6, "multiply row: [0][1] = 6");
    check(m.Get(1, 0) == 3, "multiply row: [1][0] = 3");  //не изменилась
}

void test_square_matrix_add_row_to_row() {
    SquareMatrix<int> m(2);
    m.Set(0, 0, 1); m.Set(0, 1, 2);
    m.Set(1, 0, 3); m.Set(1, 1, 4);

    //прибавляем строку 0 * 2 к строке 1
    m.AddRowToRow(0, 1, 2);

    //строка 1 = [3, 4] + 2*[1, 2] = [3+2, 4+4] = [5, 8]
    check(m.Get(1, 0) == 5, "add row to row: [1][0] = 5");
    check(m.Get(1, 1) == 8, "add row to row: [1][1] = 8");
}

void test_square_matrix_swap_cols() {
    SquareMatrix<int> m(2);
    m.Set(0, 0, 1); m.Set(0, 1, 2);
    m.Set(1, 0, 3); m.Set(1, 1, 4);

    m.SwapCols(0, 1);

    //столбцы поменялись
    check(m.Get(0, 0) == 2, "swap cols: [0][0] = 2");
    check(m.Get(0, 1) == 1, "swap cols: [0][1] = 1");
    check(m.Get(1, 0) == 4, "swap cols: [1][0] = 4");
    check(m.Get(1, 1) == 3, "swap cols: [1][1] = 3");
}

void run_test_square_matrix() {
    reset_counters();

    cout << "=== Square Matrix Tests ===" << endl;

    test_square_matrix_creation();
    test_square_matrix_set_get();
    test_square_matrix_norm();
    test_square_matrix_swap_rows();
    test_square_matrix_multiply_row();
    test_square_matrix_add_row_to_row();
    test_square_matrix_swap_cols();

    print_results();
}