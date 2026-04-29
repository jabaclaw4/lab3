#include <iostream>
#include "../src/Range.h"
#include "../src/Filters.h"
#include "../src/test_utils.h"

using namespace std;

void run_test_range_filters() {
    reset_counters();

    cout << "=== Range & Where Tests ===" << endl;

    // Range
    auto seq = Range(1, 10);
    check(seq->GetLength() == 10, "Range size = 10");
    check(seq->Get(0) == 1, "Range first = 1");
    check(seq->Get(9) == 10, "Range last = 10");

    // Where (простые числа)
    auto primes = seq->Where(isPrime);

    check(primes->GetLength() == 4, "Primes count = 4");
    check(primes->Get(0) == 2, "Prime[0] = 2");
    check(primes->Get(1) == 3, "Prime[1] = 3");
    check(primes->Get(2) == 5, "Prime[2] = 5");
    check(primes->Get(3) == 7, "Prime[3] = 7");

    // делители числа
    auto divisors = getDivisors(6);
    check(divisors->GetLength() == 4, "Divisors count = 4");
    check(divisors->Get(0) == 1, "Div[0] = 1");
    check(divisors->Get(1) == 2, "Div[1] = 2");
    check(divisors->Get(2) == 3, "Div[2] = 3");
    check(divisors->Get(3) == 6, "Div[3] = 6");

    // простые множители
    auto factors = primeFactors(12); // 2,2,3
    check(factors->GetLength() == 3, "Factors count = 3");
    check(factors->Get(0) == 2, "Factor[0] = 2");
    check(factors->Get(1) == 2, "Factor[1] = 2");
    check(factors->Get(2) == 3, "Factor[2] = 3");

    print_results();
}