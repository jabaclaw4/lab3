#include <iostream>
#include "../src/MutableVector.h"
#include "../src/test_utils.h"

using namespace std;

bool isEven(int x) {
    return x % 2 == 0;
}

int doubleVal(int x) {
    return x * 2;
}

int sumFunc(int x, int acc) {
    return x + acc;
}

void run_test_vector_functional() {
    reset_counters();

    cout << "=== Vector Functional Tests ===" << endl;

    MutableVector<int> v(3);
    v.Set(0, 1);
    v.Set(1, 2);
    v.Set(2, 3);

    // MAP
    Vector<int>* mapped = v.Map(doubleVal);
    check(mapped->Get(0) == 2, "map: 1 -> 2");
    check(mapped->Get(1) == 4, "map: 2 -> 4");
    check(mapped->Get(2) == 6, "map: 3 -> 6");

    // WHERE
    Vector<int>* filtered = v.Where(isEven);
    check(filtered->GetSize() == 1, "where: size = 1");
    check(filtered->Get(0) == 2, "where: only even = 2");

    // REDUCE
    int sum = v.Reduce(sumFunc, 0);
    check(sum == 6, "reduce: sum = 6");

    print_results();
}

void run_test_vector_mutable_ops() {
    reset_counters();

    cout << "=== MutableVector Operators Tests ===" << endl;

    MutableVector<int> v1(3);
    v1.Set(0, 1);
    v1.Set(1, 2);
    v1.Set(2, 3);

    MutableVector<int> v2(3);
    v2.Set(0, 4);
    v2.Set(1, 5);
    v2.Set(2, 6);

    // +=
    v1 += v2;  // [5,7,9]
    check(v1.Get(0) == 5, "+=: index 0");
    check(v1.Get(1) == 7, "+=: index 1");
    check(v1.Get(2) == 9, "+=: index 2");

    // -=
    v1 -= v2;  // обратно [1,2,3]
    check(v1.Get(0) == 1, "-=: index 0");
    check(v1.Get(1) == 2, "-=: index 1");
    check(v1.Get(2) == 3, "-=: index 2");

    // *=
    v1 *= 2;  // [2,4,6]
    check(v1.Get(0) == 2, "*=: index 0");
    check(v1.Get(1) == 4, "*=: index 1");
    check(v1.Get(2) == 6, "*=: index 2");

    print_results();
}