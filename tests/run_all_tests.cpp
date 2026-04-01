#include <iostream>

using namespace std;

void run_test_vector();
void run_test_complex();
void run_test_result_info();

void run_all_tests() {
    cout << "\n=== RUNNING ALL TESTS FOR LAB 3 ===" << endl;

    cout << "\n[1/3] Vector tests:" << endl;
    run_test_vector();

    cout << "\n[2/3] Complex tests:" << endl;
    run_test_complex();

    cout << "\n[3/3] ResultInfo tests:" << endl;
    run_test_result_info();
}