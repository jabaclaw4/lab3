#include <iostream>
#include <limits>
#include "src/MutableVector.h"
#include "src/ImmutableVector.h"
#include "src/Complex.h"
#include "src/SquareMatrix.h"
#include "src/all_tests.h"
//добавить форвард декларейшн для <<
using namespace std;

Vector<int>* g_vec_int = nullptr;
Vector<double>* g_vec_double = nullptr;
Vector<Complex>* g_vec_complex = nullptr;

SquareMatrix<int>* g_matrix_int = nullptr;
SquareMatrix<double>* g_matrix_double = nullptr;

enum VectorType { NONE, INT, DOUBLE, COMPLEX };
VectorType g_current_type = NONE;

void print_menu() {
    cout << "\n========================================" << endl;
    cout << "           LAB 3 - MENU" << endl;
    cout << "========================================" << endl;

    cout << "\n=== CREATE VECTORS ===" << endl;
    cout << "1  - Create MutableVector<int>" << endl;
    cout << "2  - Create ImmutableVector<int>" << endl;
    cout << "3  - Create MutableVector<double>" << endl;
    cout << "4  - Create ImmutableVector<double>" << endl;
    cout << "5  - Create MutableVector<Complex>" << endl;
    cout << "6  - Create ImmutableVector<Complex>" << endl;

    cout << "\n=== VECTOR OPERATIONS ===" << endl;
    cout << "7  - Get element by index" << endl;
    cout << "8  - Set element (Mutable only)" << endl;
    cout << "9  - Print vector" << endl;
    cout << "10 - Add two vectors" << endl;
    cout << "11 - Multiply by scalar" << endl;
    cout << "12 - Calculate Norm" << endl;
    cout << "13 - Dot product" << endl;
    cout << "14 - TryGet (safe access with ResultInfo)" << endl;

    cout << "\n=== CREATE MATRICES ===" << endl;
    cout << "20 - Create SquareMatrix<int>" << endl;
    cout << "21 - Create SquareMatrix<double>" << endl;

    cout << "\n=== MATRIX OPERATIONS ===" << endl;
    cout << "22 - Print matrix" << endl;
    cout << "23 - Get element [i][j]" << endl;
    cout << "24 - Set element [i][j]" << endl;
    cout << "25 - Add two matrices" << endl;
    cout << "26 - Multiply by scalar" << endl;
    cout << "27 - Calculate norm" << endl;
    cout << "28 - Swap rows" << endl;
    cout << "29 - Multiply row by scalar" << endl;
    cout << "30 - Add row to row" << endl;

    cout << "\n=== DEMOS & TESTS ===" << endl;
    cout << "90 - Vector operators demo" << endl;
    cout << "91 - Matrix demo" << endl;
    cout << "99 - Run ALL tests" << endl;

    cout << "\n0 - Exit" << endl;
    cout << "========================================" << endl;
    cout << "Choice: ";
}

void clear_current_vector() {
    if (g_vec_int != nullptr) {
        delete g_vec_int;
        g_vec_int = nullptr;
    }
    if (g_vec_double != nullptr) {
        delete g_vec_double;
        g_vec_double = nullptr;
    }
    if (g_vec_complex != nullptr) {
        delete g_vec_complex;
        g_vec_complex = nullptr;
    }
    g_current_type = NONE;
}

void clear_current_matrix() {
    if (g_matrix_int != nullptr) {
        delete g_matrix_int;
        g_matrix_int = nullptr;
    }
    if (g_matrix_double != nullptr) {
        delete g_matrix_double;
        g_matrix_double = nullptr;
    }
}

void test_operators_demo() {
    cout << "\n=== DEMO: Vector Operators ===" << endl;

    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};

    MutableVector<int> v1(arr1, 3);
    MutableVector<int> v2(arr2, 3);

    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;

    cout << "\nOperator []: v1[1] = " << v1[1] << endl;

    Vector<int>* v3 = v1.Add(v2);
    cout << "v1 + v2 = " << *v3 << endl;

    cout << "||v1|| = " << v1.Norm() << endl;

    int dot = v1.DotProduct(v2);
    cout << "v1 · v2 = " << dot << endl;

    Vector<int>* v4 = v1.MultiplyByScalar(2);
    cout << "2 * v1 = " << *v4 << endl;

    cout << "\n=== Double vectors ===" << endl;
    double arr3[] = {1.5, 2.5, 3.5};
    MutableVector<double> vd(arr3, 3);
    cout << "vd = " << vd << endl;
    cout << "||vd|| = " << vd.Norm() << endl;

    cout << "\n=== Complex vectors ===" << endl;
    Complex c1(1, 2);
    Complex c2(3, 4);
    Complex arr4[] = {c1, c2};
    MutableVector<Complex> vc(arr4, 2);
    cout << "vc = " << vc << endl;
    cout << "||vc|| = " << vc.Norm() << endl;

    delete v3;
    delete v4;
}

void test_matrix_demo() {
    cout << "\n=== DEMO: Square Matrix ===" << endl;

    SquareMatrix<int> m(3);

    cout << "Creating 3x3 matrix..." << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            m.Set(i, j, i * 3 + j + 1);
        }
    }

    cout << "Matrix m:" << endl;
    cout << m << endl;

    cout << "\nNorm of m: " << m.Norm() << endl;

    cout << "\nSwapping rows 0 and 2..." << endl;
    m.SwapRows(0, 2);
    cout << "After swap:" << endl;
    cout << m << endl;

    cout << "\nMultiplying row 1 by 2..." << endl;
    m.MultiplyRow(1, 2);
    cout << "After multiply:" << endl;
    cout << m << endl;

    SquareMatrix<int> m2(3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            m2.Set(i, j, 1);
        }
    }

    cout << "\nMatrix m2 (all ones):" << endl;
    cout << m2 << endl;

    Matrix<int>* m3 = m.Add(m2);
    cout << "\nm + m2:" << endl;
    cout << *m3 << endl;

    delete m3;
}

int main() {
    int choice;
    cout << "\n========================================" << endl;
    cout << "       LABORATORY WORK #3" << endl;
    cout << "   Vector & Matrix Operations" << endl;
    cout << "========================================\n" << endl;

    while (true) {
        print_menu();

        if (!(cin >> choice)) {
            cout << "\nERROR: Invalid input! Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 0) {
            cout << "\nExiting... Goodbye!" << endl;
            break;
        }

        switch (choice) {
            // CASES 1-14: VECTOR OPERATIONS (КАК БЫЛО)
            case 1: {
                // ... (твой код case 1)
                break;
            }

                // ... (все остальные cases 2-14 остаются КАК БЫЛИ)

            case 20: {  //Create SquareMatrix<int>
                clear_current_matrix();
                int size;
                cout << "Enter matrix size (n for n×n): ";
                if (!(cin >> size) || size <= 0) {
                    cout << "ERROR: Invalid size!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                g_matrix_int = new SquareMatrix<int>(size);

                cout << "Enter " << size*size << " integers (row by row):" << endl;
                for (int i = 0; i < size; i++) {
                    for (int j = 0; j < size; j++) {
                        int value;
                        cout << "Element [" << i << "][" << j << "]: ";
                        if (!(cin >> value)) {
                            cout << "ERROR: Invalid input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            delete g_matrix_int;
                            g_matrix_int = nullptr;
                            goto end_case_20;
                        }
                        g_matrix_int->Set(i, j, value);
                    }
                }

                cout << "OK: Created SquareMatrix<int>" << endl;
                cout << "Matrix:" << endl;
                cout << *g_matrix_int << endl;
                end_case_20:
                break;
            }

            case 21: {  //Create SquareMatrix<double>
                clear_current_matrix();
                int size;
                cout << "Enter matrix size (n for n×n): ";
                if (!(cin >> size) || size <= 0) {
                    cout << "ERROR: Invalid size!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                g_matrix_double = new SquareMatrix<double>(size);

                cout << "Enter " << size*size << " doubles (row by row):" << endl;
                for (int i = 0; i < size; i++) {
                    for (int j = 0; j < size; j++) {
                        double value;
                        cout << "Element [" << i << "][" << j << "]: ";
                        if (!(cin >> value)) {
                            cout << "ERROR: Invalid input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            delete g_matrix_double;
                            g_matrix_double = nullptr;
                            goto end_case_21;
                        }
                        g_matrix_double->Set(i, j, value);
                    }
                }

                cout << "OK: Created SquareMatrix<double>" << endl;
                cout << "Matrix:" << endl;
                cout << *g_matrix_double << endl;
                end_case_21:
                break;
            }

            case 22: {  //Print matrix
                if (g_matrix_int == nullptr && g_matrix_double == nullptr) {
                    cout << "ERROR: Create matrix first!" << endl;
                    break;
                }

                if (g_matrix_int != nullptr) {
                    cout << "Matrix<int>:" << endl;
                    cout << *g_matrix_int << endl;
                    cout << "Size: " << g_matrix_int->GetSize() << "×" << g_matrix_int->GetSize() << endl;
                } else if (g_matrix_double != nullptr) {
                    cout << "Matrix<double>:" << endl;
                    cout << *g_matrix_double << endl;
                    cout << "Size: " << g_matrix_double->GetSize() << "×" << g_matrix_double->GetSize() << endl;
                }
                break;
            }

            case 23: {  //Get element
                if (g_matrix_int == nullptr && g_matrix_double == nullptr) {
                    cout << "ERROR: Create matrix first!" << endl;
                    break;
                }

                int row, col;
                cout << "Enter row: ";
                if (!(cin >> row)) {
                    cout << "ERROR: Invalid input!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                cout << "Enter column: ";
                if (!(cin >> col)) {
                    cout << "ERROR: Invalid input!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                try {
                    if (g_matrix_int != nullptr) {
                        cout << "matrix[" << row << "][" << col << "] = " << g_matrix_int->Get(row, col) << endl;
                    } else if (g_matrix_double != nullptr) {
                        cout << "matrix[" << row << "][" << col << "] = " << g_matrix_double->Get(row, col) << endl;
                    }
                } catch (exception& e) {
                    cout << "ERROR: " << e.what() << endl;
                }
                break;
            }

            case 24: {  //Set element
                if (g_matrix_int == nullptr && g_matrix_double == nullptr) {
                    cout << "ERROR: Create matrix first!" << endl;
                    break;
                }

                int row, col;
                cout << "Enter row: ";
                if (!(cin >> row)) {
                    cout << "ERROR: Invalid input!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                cout << "Enter column: ";
                if (!(cin >> col)) {
                    cout << "ERROR: Invalid input!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                try {
                    if (g_matrix_int != nullptr) {
                        int value;
                        cout << "Enter value: ";
                        if (!(cin >> value)) {
                            cout << "ERROR: Invalid input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        g_matrix_int->Set(row, col, value);
                        cout << "OK: Set matrix[" << row << "][" << col << "] = " << value << endl;
                    } else if (g_matrix_double != nullptr) {
                        double value;
                        cout << "Enter value: ";
                        if (!(cin >> value)) {
                            cout << "ERROR: Invalid input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        g_matrix_double->Set(row, col, value);
                        cout << "OK: Set matrix[" << row << "][" << col << "] = " << value << endl;
                    }
                } catch (exception& e) {
                    cout << "ERROR: " << e.what() << endl;
                }
                break;
            }

            case 27: {  //Matrix norm
                if (g_matrix_int == nullptr && g_matrix_double == nullptr) {
                    cout << "ERROR: Create matrix first!" << endl;
                    break;
                }

                double norm;
                if (g_matrix_int != nullptr) {
                    norm = g_matrix_int->Norm();
                } else {
                    norm = g_matrix_double->Norm();
                }

                cout << "||matrix|| = " << norm << endl;
                break;
            }

            case 28: {  //Swap rows
                if (g_matrix_int == nullptr && g_matrix_double == nullptr) {
                    cout << "ERROR: Create matrix first!" << endl;
                    break;
                }

                int row1, row2;
                cout << "Enter first row: ";
                if (!(cin >> row1)) {
                    cout << "ERROR: Invalid input!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                cout << "Enter second row: ";
                if (!(cin >> row2)) {
                    cout << "ERROR: Invalid input!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                try {
                    if (g_matrix_int != nullptr) {
                        g_matrix_int->SwapRows(row1, row2);
                        cout << "OK: Swapped rows " << row1 << " and " << row2 << endl;
                        cout << "Matrix:" << endl;
                        cout << *g_matrix_int << endl;
                    } else if (g_matrix_double != nullptr) {
                        g_matrix_double->SwapRows(row1, row2);
                        cout << "OK: Swapped rows " << row1 << " and " << row2 << endl;
                        cout << "Matrix:" << endl;
                        cout << *g_matrix_double << endl;
                    }
                } catch (exception& e) {
                    cout << "ERROR: " << e.what() << endl;
                }
                break;
            }

            case 90: {
                test_operators_demo();
                break;
            }

            case 91: {
                test_matrix_demo();
                break;
            }

            case 99: {
                run_all_tests();
                break;
            }

            default:
                cout << "ERROR: Invalid choice!" << endl;
        }
    }

    clear_current_vector();
    clear_current_matrix();
    return 0;
}
