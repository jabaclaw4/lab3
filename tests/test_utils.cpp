#include "../src/test_utils.h"
#include <iostream>

using namespace std;

//определение глобальных переменных
int total = 0;
int passed = 0;

//проверка условия
void check(bool condition, const char* test_name) {
    total++;
    if (condition) {
        passed++;
        cout << "  OK: " << test_name << endl;
    } else {
        cout << "  FAIL: " << test_name << endl;
    }
}

//сброс счётчиков
void reset_counters() {
    total = 0;
    passed = 0;
}

//вывод результатов
void print_results() {
    cout << "\nResults: " << passed << " / " << total << " tests passed" << endl;

    if (passed == total) {
        cout << "All tests OK!" << endl;
    } else {
        cout << "Some tests FAILED!" << endl;
    }
}