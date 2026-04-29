#include <iostream>

using namespace std;

void run_test_vector();
void run_test_complex();
void run_test_result_info();
void run_test_range_filters();
void run_test_vector_functional();
void run_test_vector_mutable_ops();

void run_all_tests() {
    cout << "\n=== RUNNING ALL TESTS FOR LAB 3 ===" << endl;

    cout << "\n[1/5] Vector tests:" << endl;
    run_test_vector();

    cout << "\n[2/5] Complex tests:" << endl;
    run_test_complex();

    cout << "\n[3/5] ResultInfo tests:" << endl;
    run_test_result_info();

    cout << "\n[4/5] RangeFilters (A-3) tests:" << endl;
    run_test_range_filters();

    cout << "\n[4/5] Reduce/map/where (vector) and Mutable ops (vector) tests:" << endl;
    run_test_vector_functional();
    run_test_vector_mutable_ops();
}