#include <iostream>
#include <limits>
#include "src/MutableVector.h"
#include "src/ImmutableVector.h"
#include "src/Complex.h"
#include "src/all_tests.h"
//добавить побольше методом из монады чтобы поттрогать их именно
//map reduce + вопрос с выводом в консоль как сделать так чтобы не создавать каждый раз ТипUtils h для нового АТД
//еще че нибудь на доп баллы
using namespace std;

//глобальные указатели на текущие векторы
Vector<int>* g_vec_int = nullptr;
Vector<double>* g_vec_double = nullptr;
Vector<Complex>* g_vec_complex = nullptr;

enum VectorType { NONE, INT, DOUBLE, COMPLEX }; //Хранилище типа текущего активного вектора
//Индикатор состояния (есть вектор или нет)
VectorType g_current_type = NONE;//Флаг, который говорит: "Сейчас активен вектор типа такогото

void print_menu() {
    cout << "\n===== MENU =====" << endl;
    cout << "=== Create Vectors ===" << endl;
    cout << "1 - Create MutableVector<int>" << endl;
    cout << "2 - Create ImmutableVector<int>" << endl;
    cout << "3 - Create MutableVector<double>" << endl;
    cout << "4 - Create ImmutableVector<double>" << endl;
    cout << "5 - Create MutableVector<Complex>" << endl;
    cout << "6 - Create ImmutableVector<Complex>" << endl;

    cout << "\n=== Vector Operations ===" << endl;
    cout << "7 - Get element by index" << endl;
    cout << "8 - Set element by index (Mutable only)" << endl;
    cout << "9 - Print vector" << endl;
    cout << "10 - Add two vectors" << endl;
    cout << "11 - Multiply by scalar" << endl;
    cout << "12 - Calculate Norm" << endl;
    cout << "13 - Dot product with another vector" << endl;

    cout << "\n=== Demos & Tests ===" << endl;
    cout << "14 - Operators demo" << endl;
    cout << "15 - Run ALL tests" << endl;

    cout << "\n0 - Exit" << endl;
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

void test_operators_demo() {
    cout << "\n=== DEMO: Operators ===" << endl;

    //создаём два вектора
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};

    MutableVector<int> v1(arr1, 3);
    MutableVector<int> v2(arr2, 3);

    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;

    //оператор []
    cout << "\nOperator []: v1[1] = " << v1[1] << endl;

    //оператор + (если реализован)
    cout << "\nVector operations:" << endl;
    Vector<int>* v3 = v1.Add(v2);
    cout << "v1.Add(v2) = " << *v3 << endl;

    //норма
    cout << "||v1|| = " << v1.Norm() << endl;

    //скалярное произведение
    int dot = v1.DotProduct(v2);
    cout << "v1 · v2 = " << dot << endl;

    //умножение на скаляр
    Vector<int>* v4 = v1.MultiplyByScalar(2);
    cout << "2 * v1 = " << *v4 << endl;

    //демонстрация с double
    cout << "\n=== Double vectors ===" << endl;
    double arr3[] = {1.5, 2.5, 3.5};
    MutableVector<double> vd(arr3, 3);
    cout << "vd = " << vd << endl;
    cout << "||vd|| = " << vd.Norm() << endl;

    //демонстрация с Complex
    cout << "\n=== Complex vectors ===" << endl;
    Complex c1(1, 2);  //1 + 2i
    Complex c2(3, 4);  //3 + 4i
    Complex arr4[] = {c1, c2};
    MutableVector<Complex> vc(arr4, 2);
    cout << "vc = " << vc << endl;
    cout << "||vc|| = " << vc.Norm() << endl;

    delete v3;
    delete v4;
}

int main() {
    int choice;
    cout << "LAB 3 - Vector Demo" << endl;

    while (true) {
        print_menu();

        //защита от неправильного ввода
        if (!(cin >> choice)) {
            cout << "\nERROR: Invalid input! Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 0) {
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

            case 14: {  //TryGet (safe get)
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
                test_operators_demo();
                break;
            }

            case 16: {
                run_all_tests();
                break;
            }

            default:
                cout << "ERROR: Invalid choice! Please choose 0-16" << endl;
        }
    }

    clear_current_vector();
    return 0;
}

