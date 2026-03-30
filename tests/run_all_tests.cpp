#include <iostream>
#include "../src/all_tests.h"
using namespace std;

int main() {
    cout << "=== RUNNING ALL TESTS FOR LAB 3 ===" << endl;

    cout << "\n[1/3] Vector tests:" << endl;
    run_test_vector();

    cout << "\n[2/3] Complex tests:" << endl;
    run_test_complex();

    cout << "\n[2/3] ResultInfo tests:" << endl;
    run_test_result_info();
    return 0;
}
