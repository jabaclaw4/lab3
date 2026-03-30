#include <iostream>
#include "../src/MutableVector.h"
#include "../src/ImmutableVector.h"
#include "../src/ResultInfo.h"
#include "../src/test_utils.h"

using namespace std;

void test_result_info_success() {
    //создание успешного результата
    ResultInfo<int> result = ResultInfo<int>::Success(42);

    check(result.IsSuccess(), "ResultInfo: Success is success");
    check(!result.IsFailure(), "ResultInfo: Success is not failure");
    check(result.GetValue() == 42, "ResultInfo: Success has correct value");
}

void test_result_info_failure() {
    //создание неуспешного результата
    ResultInfo<int> result = ResultInfo<int>::Failure("error message");

    check(!result.IsSuccess(), "ResultInfo: Failure is not success");
    check(result.IsFailure(), "ResultInfo: Failure is failure");
    check(result.GetError() == "error message", "ResultInfo: Failure has correct error");
}

void test_result_info_with_vector() {
    int arr[] = {10, 20, 30};
    MutableVector<int> v(arr, 3);

    //успешное получение элемента
    ResultInfo<int> result1 = v.TryGet(1);
    check(result1.IsSuccess(), "Vector TryGet: valid index success");
    check(result1.GetValue() == 20, "Vector TryGet: correct value");

    //неуспешное получение элемента
    ResultInfo<int> result2 = v.TryGet(10);
    check(result2.IsFailure(), "Vector TryGet: invalid index failure");
    check(result2.GetError() == "index out of range", "Vector TryGet: correct error");
}

void test_result_info_boundary_cases() {
    int arr[] = {100, 200, 300};
    MutableVector<int> v(arr, 3);

    //первый элемент
    ResultInfo<int> result1 = v.TryGet(0);
    check(result1.IsSuccess(), "TryGet: first element (index 0)");
    check(result1.GetValue() == 100, "TryGet: first element value");

    //последний элемент
    ResultInfo<int> result2 = v.TryGet(2);
    check(result2.IsSuccess(), "TryGet: last element");
    check(result2.GetValue() == 300, "TryGet: last element value");

    //отрицательный индекс
    ResultInfo<int> result3 = v.TryGet(-1);
    check(result3.IsFailure(), "TryGet: negative index fails");

    //индекс равен размеру
    ResultInfo<int> result4 = v.TryGet(3);
    check(result4.IsFailure(), "TryGet: index == size fails");

    //индекс больше размера
    ResultInfo<int> result5 = v.TryGet(100);
    check(result5.IsFailure(), "TryGet: index > size fails");
}

void test_result_info_different_types() {
    //тест с double
    double arr_d[] = {1.5, 2.5, 3.5};
    MutableVector<double> vd(arr_d, 3);

    ResultInfo<double> result_d = vd.TryGet(1);
    check(result_d.IsSuccess(), "TryGet double: success");
    check(result_d.GetValue() == 2.5, "TryGet double: correct value");

    //тест с Complex
    Complex c1(1, 2);
    Complex c2(3, 4);
    Complex arr_c[] = {c1, c2};
    MutableVector<Complex> vc(arr_c, 2);

    ResultInfo<Complex> result_c = vc.TryGet(0);
    check(result_c.IsSuccess(), "TryGet Complex: success");
    check(result_c.GetValue().GetReal() == 1, "TryGet Complex: correct real part");
    check(result_c.GetValue().GetImag() == 2, "TryGet Complex: correct imag part");
}

void test_result_info_immutable_vector() {
    //проверяем что TryGet работает с ImmutableVector
    int arr[] = {5, 10, 15};
    ImmutableVector<int> v(arr, 3);

    ResultInfo<int> result1 = v.TryGet(2);
    check(result1.IsSuccess(), "ImmutableVector TryGet: success");
    check(result1.GetValue() == 15, "ImmutableVector TryGet: correct value");

    ResultInfo<int> result2 = v.TryGet(5);
    check(result2.IsFailure(), "ImmutableVector TryGet: out of range");
}

void run_test_result_info() {
    reset_counters();

    cout << "=== ResultInfo Tests ===" << endl;

    test_result_info_success();
    test_result_info_failure();
    test_result_info_with_vector();
    test_result_info_boundary_cases();
    test_result_info_different_types();
    test_result_info_immutable_vector();

    print_results();
}