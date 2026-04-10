#include <iostream>
#include <limits>//для обработки ошибок если ввели не то
#include "src/MutableVector.h"
#include "src/ImmutableVector.h"
#include "src/Complex.h"
#include "src/SquareMatrix.h"
#include "src/all_tests.h"

using namespace std;

Vector<int>* g_vec_int = nullptr; //без этого вектор создался бы и сразу удалился нельзя было бы работать с ним в следующих операциях
Vector<double>* g_vec_double = nullptr;
Vector<Complex>* g_vec_complex = nullptr;

SquareMatrix<int>* g_matrix_int = nullptr;// то же самое для матрицы
SquareMatrix<double>* g_matrix_double = nullptr;

enum VectorType { NONE, INT, DOUBLE, COMPLEX };
VectorType g_current_type = NONE;
//чтобы понимать какой вектор именно сейчас активен и че выводить
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
    cout << "15 - Create SquareMatrix<int>" << endl;
    cout << "16 - Create SquareMatrix<double>" << endl;

    cout << "\n=== MATRIX OPERATIONS ===" << endl;
    cout << "17 - Print matrix" << endl;
    cout << "18 - Get element [i][j]" << endl;
    cout << "19 - Set element [i][j]" << endl;
    cout << "20 - Add two matrices" << endl;
    cout << "21 - Multiply by scalar" << endl;
    cout << "22 - Calculate norm" << endl;
    cout << "23 - Swap rows" << endl;
    cout << "24 - Multiply row by scalar" << endl;
    cout << "25 - Add row to row" << endl;
    cout << "26 - Swap columns" << endl;

    cout << "\n=== DEMOS & TESTS ===" << endl;
    cout << "30 - Vector operators demo" << endl;
    cout << "31 - Matrix demo" << endl;
    cout << "32 - Run ALL tests" << endl;

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
            case 1: {
                clear_current_vector();
                int size;
                cout << "Enter vector size: ";
                if (!(cin >> size) || size < 0) {
                    cout << "ERROR: Invalid size!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                if (size == 0) {
                    g_vec_int = new MutableVector<int>();
                } else {
                    int* arr = new int[size];
                    cout << "Enter " << size << " integers:" << endl;
                    for (int i = 0; i < size; i++) {
                        cout << "Element " << i << ": ";
                        if (!(cin >> arr[i])) {
                            cout << "ERROR: Invalid input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            delete[] arr;
                            goto end_case_1;
                        }
                    }
                    g_vec_int = new MutableVector<int>(arr, size);
                    delete[] arr;
                }

                g_current_type = INT;
                cout << "OK: Created MutableVector<int>" << endl;
                cout << "Vector: " << *g_vec_int << endl;
                end_case_1:
                break;
            }

            case 2: {
                clear_current_vector();
                int size;
                cout << "Enter vector size: ";
                if (!(cin >> size) || size < 0) {
                    cout << "ERROR: Invalid size!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                if (size == 0) {
                    g_vec_int = new ImmutableVector<int>();
                } else {
                    int* arr = new int[size];
                    cout << "Enter " << size << " integers:" << endl;
                    for (int i = 0; i < size; i++) {
                        cout << "Element " << i << ": ";
                        if (!(cin >> arr[i])) {
                            cout << "ERROR: Invalid input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            delete[] arr;
                            goto end_case_2;
                        }
                    }
                    g_vec_int = new ImmutableVector<int>(arr, size);
                    delete[] arr;
                }

                g_current_type = INT;
                cout << "OK: Created ImmutableVector<int>" << endl;
                cout << "Vector: " << *g_vec_int << endl;
                end_case_2:
                break;
            }

            case 3: {
                clear_current_vector();
                int size;
                cout << "Enter vector size: ";
                if (!(cin >> size) || size < 0) {
                    cout << "ERROR: Invalid size!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                if (size == 0) {
                    g_vec_double = new MutableVector<double>();
                } else {
                    double* arr = new double[size];
                    cout << "Enter " << size << " doubles:" << endl;
                    for (int i = 0; i < size; i++) {
                        cout << "Element " << i << ": ";
                        if (!(cin >> arr[i])) {
                            cout << "ERROR: Invalid input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            delete[] arr;
                            goto end_case_3;
                        }
                    }
                    g_vec_double = new MutableVector<double>(arr, size);
                    delete[] arr;
                }

                g_current_type = DOUBLE;
                cout << "OK: Created MutableVector<double>" << endl;
                cout << "Vector: " << *g_vec_double << endl;
                end_case_3:
                break;
            }

            case 4: {
                clear_current_vector();
                int size;
                cout << "Enter vector size: ";
                if (!(cin >> size) || size < 0) {
                    cout << "ERROR: Invalid size!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                if (size == 0) {
                    g_vec_double = new ImmutableVector<double>();
                } else {
                    double* arr = new double[size];
                    cout << "Enter " << size << " doubles:" << endl;
                    for (int i = 0; i < size; i++) {
                        cout << "Element " << i << ": ";
                        if (!(cin >> arr[i])) {
                            cout << "ERROR: Invalid input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            delete[] arr;
                            goto end_case_4;
                        }
                    }
                    g_vec_double = new ImmutableVector<double>(arr, size);
                    delete[] arr;
                }

                g_current_type = DOUBLE;
                cout << "OK: Created ImmutableVector<double>" << endl;
                cout << "Vector: " << *g_vec_double << endl;
                end_case_4:
                break;
            }

            case 5: {
                clear_current_vector();
                int size;
                cout << "Enter vector size: ";
                if (!(cin >> size) || size < 0) {
                    cout << "ERROR: Invalid size!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                if (size == 0) {
                    g_vec_complex = new MutableVector<Complex>();
                } else {
                    Complex* arr = new Complex[size];
                    cout << "Enter " << size << " complex numbers (real imag):" << endl;
                    for (int i = 0; i < size; i++) {
                        double real, imag;
                        cout << "Element " << i << " (real imag): ";
                        if (!(cin >> real >> imag)) {
                            cout << "ERROR: Invalid input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            delete[] arr;
                            goto end_case_5;
                        }
                        arr[i] = Complex(real, imag);
                    }
                    g_vec_complex = new MutableVector<Complex>(arr, size);
                    delete[] arr;
                }

                g_current_type = COMPLEX;
                cout << "OK: Created MutableVector<Complex>" << endl;
                cout << "Vector: " << *g_vec_complex << endl;
                end_case_5:
                break;
            }

            case 6: {
                clear_current_vector();
                int size;
                cout << "Enter vector size: ";
                if (!(cin >> size) || size < 0) {
                    cout << "ERROR: Invalid size!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                if (size == 0) {
                    g_vec_complex = new ImmutableVector<Complex>();
                } else {
                    Complex* arr = new Complex[size];
                    cout << "Enter " << size << " complex numbers (real imag):" << endl;
                    for (int i = 0; i < size; i++) {
                        double real, imag;
                        cout << "Element " << i << " (real imag): ";
                        if (!(cin >> real >> imag)) {
                            cout << "ERROR: Invalid input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            delete[] arr;
                            goto end_case_6;
                        }
                        arr[i] = Complex(real, imag);
                    }
                    g_vec_complex = new ImmutableVector<Complex>(arr, size);
                    delete[] arr;
                }

                g_current_type = COMPLEX;
                cout << "OK: Created ImmutableVector<Complex>" << endl;
                cout << "Vector: " << *g_vec_complex << endl;
                end_case_6:
                break;
            }

            case 7: {
                if (g_current_type == NONE) {
                    cout << "ERROR: Create vector first!" << endl;
                    break;
                }

                int index;
                cout << "Enter index: ";
                if (!(cin >> index)) {
                    cout << "ERROR: Invalid input!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                try {
                    if (g_current_type == INT) {
                        cout << "vec[" << index << "] = " << g_vec_int->Get(index) << endl;
                    } else if (g_current_type == DOUBLE) {
                        cout << "vec[" << index << "] = " << g_vec_double->Get(index) << endl;
                    } else if (g_current_type == COMPLEX) {
                        cout << "vec[" << index << "] = " << g_vec_complex->Get(index) << endl;
                    }
                } catch (exception& e) {
                    cout << "ERROR: " << e.what() << endl;
                }
                break;
            }

            case 8: {
                if (g_current_type == NONE) {
                    cout << "ERROR: Create vector first!" << endl;
                    break;
                }

                int index;
                cout << "Enter index: ";
                if (!(cin >> index)) {
                    cout << "ERROR: Invalid input!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                try {
                    if (g_current_type == INT) {
                        MutableVector<int>* mv = dynamic_cast<MutableVector<int>*>(g_vec_int);
                        if (mv == nullptr) {
                            cout << "ERROR: Vector is immutable!" << endl;
                            break;
                        }
                        int value;
                        cout << "Enter new value: ";
                        if (!(cin >> value)) {
                            cout << "ERROR: Invalid input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        mv->Set(index, value);
                        cout << "OK: Set vec[" << index << "] = " << value << endl;
                    } else if (g_current_type == DOUBLE) {
                        MutableVector<double>* mv = dynamic_cast<MutableVector<double>*>(g_vec_double);
                        if (mv == nullptr) {
                            cout << "ERROR: Vector is immutable!" << endl;
                            break;
                        }
                        double value;
                        cout << "Enter new value: ";
                        if (!(cin >> value)) {
                            cout << "ERROR: Invalid input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        mv->Set(index, value);
                        cout << "OK: Set vec[" << index << "] = " << value << endl;
                    } else if (g_current_type == COMPLEX) {
                        MutableVector<Complex>* mv = dynamic_cast<MutableVector<Complex>*>(g_vec_complex);
                        if (mv == nullptr) {
                            cout << "ERROR: Vector is immutable!" << endl;
                            break;
                        }
                        double real, imag;
                        cout << "Enter new value (real imag): ";
                        if (!(cin >> real >> imag)) {
                            cout << "ERROR: Invalid input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        mv->Set(index, Complex(real, imag));
                        cout << "OK: Set vec[" << index << "] = " << Complex(real, imag) << endl;
                    }
                } catch (exception& e) {
                    cout << "ERROR: " << e.what() << endl;
                }
                break;
            }

            case 9: {
                if (g_current_type == NONE) {
                    cout << "ERROR: Create vector first!" << endl;
                    break;
                }

                if (g_current_type == INT) {
                    cout << "Vector: " << *g_vec_int << endl;
                    cout << "Size: " << g_vec_int->GetSize() << endl;
                } else if (g_current_type == DOUBLE) {
                    cout << "Vector: " << *g_vec_double << endl;
                    cout << "Size: " << g_vec_double->GetSize() << endl;
                } else if (g_current_type == COMPLEX) {
                    cout << "Vector: " << *g_vec_complex << endl;
                    cout << "Size: " << g_vec_complex->GetSize() << endl;
                }
                break;
            }

            case 10: {
                if (g_current_type == NONE) {
                    cout << "ERROR: Create vector first!" << endl;
                    break;
                }

                cout << "Create second vector (same type and size):" << endl;

                try {
                    if (g_current_type == INT) {
                        int size = g_vec_int->GetSize();
                        int* arr = new int[size];
                        cout << "Enter " << size << " integers:" << endl;
                        for (int i = 0; i < size; i++) {
                            cout << "Element " << i << ": ";
                            if (!(cin >> arr[i])) {
                                cout << "ERROR: Invalid input!" << endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                delete[] arr;
                                goto end_case_10;
                            }
                        }
                        MutableVector<int> v2(arr, size);
                        delete[] arr;

                        Vector<int>* result = g_vec_int->Add(v2);
                        cout << "vec1 = " << *g_vec_int << endl;
                        cout << "vec2 = " << v2 << endl;
                        cout << "vec1 + vec2 = " << *result << endl;
                        delete result;
                    } else if (g_current_type == DOUBLE) {
                        int size = g_vec_double->GetSize();
                        double* arr = new double[size];
                        cout << "Enter " << size << " doubles:" << endl;
                        for (int i = 0; i < size; i++) {
                            cout << "Element " << i << ": ";
                            if (!(cin >> arr[i])) {
                                cout << "ERROR: Invalid input!" << endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                delete[] arr;
                                goto end_case_10;
                            }
                        }
                        MutableVector<double> v2(arr, size);
                        delete[] arr;

                        Vector<double>* result = g_vec_double->Add(v2);
                        cout << "vec1 = " << *g_vec_double << endl;
                        cout << "vec2 = " << v2 << endl;
                        cout << "vec1 + vec2 = " << *result << endl;
                        delete result;
                    } else if (g_current_type == COMPLEX) {
                        int size = g_vec_complex->GetSize();
                        Complex* arr = new Complex[size];
                        cout << "Enter " << size << " complex numbers (real imag):" << endl;
                        for (int i = 0; i < size; i++) {
                            double real, imag;
                            cout << "Element " << i << " (real imag): ";
                            if (!(cin >> real >> imag)) {
                                cout << "ERROR: Invalid input!" << endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                delete[] arr;
                                goto end_case_10;
                            }
                            arr[i] = Complex(real, imag);
                        }
                        MutableVector<Complex> v2(arr, size);
                        delete[] arr;

                        Vector<Complex>* result = g_vec_complex->Add(v2);
                        cout << "vec1 = " << *g_vec_complex << endl;
                        cout << "vec2 = " << v2 << endl;
                        cout << "vec1 + vec2 = " << *result << endl;
                        delete result;
                    }
                } catch (exception& e) {
                    cout << "ERROR: " << e.what() << endl;
                }
                end_case_10:
                break;
            }

            case 11: {
                if (g_current_type == NONE) {
                    cout << "ERROR: Create vector first!" << endl;
                    break;
                }

                try {
                    if (g_current_type == INT) {
                        int scalar;
                        cout << "Enter scalar: ";
                        if (!(cin >> scalar)) {
                            cout << "ERROR: Invalid input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        Vector<int>* result = g_vec_int->MultiplyByScalar(scalar);
                        cout << "vec = " << *g_vec_int << endl;
                        cout << scalar << " * vec = " << *result << endl;
                        delete result;
                    } else if (g_current_type == DOUBLE) {
                        double scalar;
                        cout << "Enter scalar: ";
                        if (!(cin >> scalar)) {
                            cout << "ERROR: Invalid input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        Vector<double>* result = g_vec_double->MultiplyByScalar(scalar);
                        cout << "vec = " << *g_vec_double << endl;
                        cout << scalar << " * vec = " << *result << endl;
                        delete result;
                    } else if (g_current_type == COMPLEX) {
                        double real, imag;
                        cout << "Enter scalar (real imag): ";
                        if (!(cin >> real >> imag)) {
                            cout << "ERROR: Invalid input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        Complex scalar(real, imag);
                        Vector<Complex>* result = g_vec_complex->MultiplyByScalar(scalar);
                        cout << "vec = " << *g_vec_complex << endl;
                        cout << scalar << " * vec = " << *result << endl;
                        delete result;
                    }
                } catch (exception& e) {
                    cout << "ERROR: " << e.what() << endl;
                }
                break;
            }

            case 12: {
                if (g_current_type == NONE) {
                    cout << "ERROR: Create vector first!" << endl;
                    break;
                }

                double norm;
                if (g_current_type == INT) {
                    norm = g_vec_int->Norm();
                } else if (g_current_type == DOUBLE) {
                    norm = g_vec_double->Norm();
                } else if (g_current_type == COMPLEX) {
                    norm = g_vec_complex->Norm();
                }

                cout << "||vec|| = " << norm << endl;
                break;
            }

            case 13: {
                if (g_current_type == NONE) {
                    cout << "ERROR: Create vector first!" << endl;
                    break;
                }

                cout << "Create second vector (same type and size):" << endl;

                try {
                    if (g_current_type == INT) {
                        int size = g_vec_int->GetSize();
                        int* arr = new int[size];
                        cout << "Enter " << size << " integers:" << endl;
                        for (int i = 0; i < size; i++) {
                            cout << "Element " << i << ": ";
                            if (!(cin >> arr[i])) {
                                cout << "ERROR: Invalid input!" << endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                delete[] arr;
                                goto end_case_13;
                            }
                        }
                        MutableVector<int> v2(arr, size);
                        delete[] arr;

                        int result = g_vec_int->DotProduct(v2);
                        cout << "vec1 = " << *g_vec_int << endl;
                        cout << "vec2 = " << v2 << endl;
                        cout << "vec1 · vec2 = " << result << endl;
                    } else if (g_current_type == DOUBLE) {
                        int size = g_vec_double->GetSize();
                        double* arr = new double[size];
                        cout << "Enter " << size << " doubles:" << endl;
                        for (int i = 0; i < size; i++) {
                            cout << "Element " << i << ": ";
                            if (!(cin >> arr[i])) {
                                cout << "ERROR: Invalid input!" << endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                delete[] arr;
                                goto end_case_13;
                            }
                        }
                        MutableVector<double> v2(arr, size);
                        delete[] arr;

                        double result = g_vec_double->DotProduct(v2);
                        cout << "vec1 = " << *g_vec_double << endl;
                        cout << "vec2 = " << v2 << endl;
                        cout << "vec1 · vec2 = " << result << endl;
                    } else if (g_current_type == COMPLEX) {
                        int size = g_vec_complex->GetSize();
                        Complex* arr = new Complex[size];
                        cout << "Enter " << size << " complex numbers (real imag):" << endl;
                        for (int i = 0; i < size; i++) {
                            double real, imag;
                            cout << "Element " << i << " (real imag): ";
                            if (!(cin >> real >> imag)) {
                                cout << "ERROR: Invalid input!" << endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                delete[] arr;
                                goto end_case_13;
                            }
                            arr[i] = Complex(real, imag);
                        }
                        MutableVector<Complex> v2(arr, size);
                        delete[] arr;

                        Complex result = g_vec_complex->DotProduct(v2);
                        cout << "vec1 = " << *g_vec_complex << endl;
                        cout << "vec2 = " << v2 << endl;
                        cout << "vec1 · vec2 = " << result << endl;
                    }
                } catch (exception& e) {
                    cout << "ERROR: " << e.what() << endl;
                }
                end_case_13:
                break;
            }

            case 14: {
                if (g_current_type == NONE) {
                    cout << "ERROR: Create vector first!" << endl;
                    break;
                }

                int index;
                cout << "Enter index: ";
                if (!(cin >> index)) {
                    cout << "ERROR: Invalid input!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                if (g_current_type == INT) {
                    ResultInfo<int> result = g_vec_int->TryGet(index);

                    if (result.IsSuccess()) {
                        cout << "OK: Success! vec[" << index << "] = " << result.GetValue() << endl;
                    } else {
                        cout << "ERROR: " << result.GetError() << endl;
                    }
                } else if (g_current_type == DOUBLE) {
                    ResultInfo<double> result = g_vec_double->TryGet(index);

                    if (result.IsSuccess()) {
                        cout << "OK: Success! vec[" << index << "] = " << result.GetValue() << endl;
                    } else {
                        cout << "ERROR: " << result.GetError() << endl;
                    }
                } else if (g_current_type == COMPLEX) {
                    ResultInfo<Complex> result = g_vec_complex->TryGet(index);

                    if (result.IsSuccess()) {
                        cout << "OK: Success! vec[" << index << "] = " << result.GetValue() << endl;
                    } else {
                        cout << "ERROR: " << result.GetError() << endl;
                    }
                }
                break;
            }

            case 15: {
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
                            goto end_case_15;
                        }
                        g_matrix_int->Set(i, j, value);
                    }
                }

                cout << "OK: Created SquareMatrix<int>" << endl;
                cout << "Matrix:" << endl;
                cout << *g_matrix_int << endl;
                end_case_15:
                break;
            }

            case 16: {
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
                            goto end_case_16;
                        }
                        g_matrix_double->Set(i, j, value);
                    }
                }

                cout << "OK: Created SquareMatrix<double>" << endl;
                cout << "Matrix:" << endl;
                cout << *g_matrix_double << endl;
                end_case_16:
                break;
            }

            case 17: {
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

            case 18: {
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

            case 19: {
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

            case 20: {
                if (g_matrix_int == nullptr && g_matrix_double == nullptr) {
                    cout << "ERROR: Create matrix first!" << endl;
                    break;
                }

                cout << "Create second matrix (same type and size):" << endl;

                try {
                    if (g_matrix_int != nullptr) {
                        int size = g_matrix_int->GetSize();
                        SquareMatrix<int> m2(size);

                        cout << "Enter " << size*size << " integers (row by row):" << endl;
                        for (int i = 0; i < size; i++) {
                            for (int j = 0; j < size; j++) {
                                int value;
                                cout << "Element [" << i << "][" << j << "]: ";
                                if (!(cin >> value)) {
                                    cout << "ERROR: Invalid input!" << endl;
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    goto end_case_20;
                                }
                                m2.Set(i, j, value);
                            }
                        }

                        Matrix<int>* result = g_matrix_int->Add(m2);
                        cout << "matrix1 = " << *g_matrix_int << endl;
                        cout << "matrix2 = " << m2 << endl;
                        cout << "matrix1 + matrix2 = " << *result << endl;
                        delete result;
                    } else if (g_matrix_double != nullptr) {
                        int size = g_matrix_double->GetSize();
                        SquareMatrix<double> m2(size);

                        cout << "Enter " << size*size << " doubles (row by row):" << endl;
                        for (int i = 0; i < size; i++) {
                            for (int j = 0; j < size; j++) {
                                double value;
                                cout << "Element [" << i << "][" << j << "]: ";
                                if (!(cin >> value)) {
                                    cout << "ERROR: Invalid input!" << endl;
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    goto end_case_20;
                                }
                                m2.Set(i, j, value);
                            }
                        }

                        Matrix<double>* result = g_matrix_double->Add(m2);
                        cout << "matrix1 = " << *g_matrix_double << endl;
                        cout << "matrix2 = " << m2 << endl;
                        cout << "matrix1 + matrix2 = " << *result << endl;
                        delete result;
                    }
                } catch (exception& e) {
                    cout << "ERROR: " << e.what() << endl;
                }
                end_case_20:
                break;
            }

            case 21: {
                if (g_matrix_int == nullptr && g_matrix_double == nullptr) {
                    cout << "ERROR: Create matrix first!" << endl;
                    break;
                }

                try {
                    if (g_matrix_int != nullptr) {
                        int scalar;
                        cout << "Enter scalar: ";
                        if (!(cin >> scalar)) {
                            cout << "ERROR: Invalid input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        Matrix<int>* result = g_matrix_int->MultiplyByScalar(scalar);
                        cout << "matrix = " << *g_matrix_int << endl;
                        cout << scalar << " * matrix = " << *result << endl;
                        delete result;
                    } else if (g_matrix_double != nullptr) {
                        double scalar;
                        cout << "Enter scalar: ";
                        if (!(cin >> scalar)) {
                            cout << "ERROR: Invalid input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        Matrix<double>* result = g_matrix_double->MultiplyByScalar(scalar);
                        cout << "matrix = " << *g_matrix_double << endl;
                        cout << scalar << " * matrix = " << *result << endl;
                        delete result;
                    }
                } catch (exception& e) {
                    cout << "ERROR: " << e.what() << endl;
                }
                break;
            }

            case 22: {
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

            case 23: {
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

            case 24: {
                if (g_matrix_int == nullptr && g_matrix_double == nullptr) {
                    cout << "ERROR: Create matrix first!" << endl;
                    break;
                }

                int row;
                cout << "Enter row: ";
                if (!(cin >> row)) {
                    cout << "ERROR: Invalid input!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                try {
                    if (g_matrix_int != nullptr) {
                        int scalar;
                        cout << "Enter scalar: ";
                        if (!(cin >> scalar)) {
                            cout << "ERROR: Invalid input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        g_matrix_int->MultiplyRow(row, scalar);
                        cout << "OK: Multiplied row " << row << " by " << scalar << endl;
                        cout << "Matrix:" << endl;
                        cout << *g_matrix_int << endl;
                    } else if (g_matrix_double != nullptr) {
                        double scalar;
                        cout << "Enter scalar: ";
                        if (!(cin >> scalar)) {
                            cout << "ERROR: Invalid input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        g_matrix_double->MultiplyRow(row, scalar);
                        cout << "OK: Multiplied row " << row << " by " << scalar << endl;
                        cout << "Matrix:" << endl;
                        cout << *g_matrix_double << endl;
                    }
                } catch (exception& e) {
                    cout << "ERROR: " << e.what() << endl;
                }
                break;
            }

            case 25: {
                if (g_matrix_int == nullptr && g_matrix_double == nullptr) {
                    cout << "ERROR: Create matrix first!" << endl;
                    break;
                }

                int sourceRow, targetRow;
                cout << "Enter source row: ";
                if (!(cin >> sourceRow)) {
                    cout << "ERROR: Invalid input!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                cout << "Enter target row: ";
                if (!(cin >> targetRow)) {
                    cout << "ERROR: Invalid input!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                try {
                    if (g_matrix_int != nullptr) {
                        int scalar;
                        cout << "Enter scalar: ";
                        if (!(cin >> scalar)) {
                            cout << "ERROR: Invalid input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        g_matrix_int->AddRowToRow(sourceRow, targetRow, scalar);
                        cout << "OK: Added row " << sourceRow << " * " << scalar << " to row " << targetRow << endl;
                        cout << "Matrix:" << endl;
                        cout << *g_matrix_int << endl;
                    } else if (g_matrix_double != nullptr) {
                        double scalar;
                        cout << "Enter scalar: ";
                        if (!(cin >> scalar)) {
                            cout << "ERROR: Invalid input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        g_matrix_double->AddRowToRow(sourceRow, targetRow, scalar);
                        cout << "OK: Added row " << sourceRow << " * " << scalar << " to row " << targetRow << endl;
                        cout << "Matrix:" << endl;
                        cout << *g_matrix_double << endl;
                    }
                } catch (exception& e) {
                    cout << "ERROR: " << e.what() << endl;
                }
                break;
            }

            case 26: {
                if (g_matrix_int == nullptr && g_matrix_double == nullptr) {
                    cout << "ERROR: Create matrix first!" << endl;
                    break;
                }

                int col1, col2;
                cout << "Enter first column: ";
                if (!(cin >> col1)) {
                    cout << "ERROR: Invalid input!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                cout << "Enter second column: ";
                if (!(cin >> col2)) {
                    cout << "ERROR: Invalid input!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                try {
                    if (g_matrix_int != nullptr) {
                        g_matrix_int->SwapCols(col1, col2);
                        cout << "OK: Swapped columns " << col1 << " and " << col2 << endl;
                        cout << "Matrix:" << endl;
                        cout << *g_matrix_int << endl;
                    } else if (g_matrix_double != nullptr) {
                        g_matrix_double->SwapCols(col1, col2);
                        cout << "OK: Swapped columns " << col1 << " and " << col2 << endl;
                        cout << "Matrix:" << endl;
                        cout << *g_matrix_double << endl;
                    }
                } catch (exception& e) {
                    cout << "ERROR: " << e.what() << endl;
                }
                break;
            }

            case 30: {
                test_operators_demo();
                break;
            }

            case 31: {
                test_matrix_demo();
                break;
            }

            case 32: {
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