#ifndef FILTERS_H
#define FILTERS_H

#include "MutableArraySequence.h"
#include "Sequence.h"

//а-3
bool isPrime(int x) {
    if (x < 2) return false;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

Sequence<int>* getDivisors(int x) {
    auto* result = new MutableArraySequence<int>();
    for (int i = 1; i <= x; i++) {
        if (x % i == 0)
            result->Append(i);
    }
    return result;
}

Sequence<int>* primeFactors(int x) {
    auto* result = new MutableArraySequence<int>();

    for (int i = 2; i <= x; i++) {
        while (x % i == 0) {
            result->Append(i);
            x /= i;
        }
    }
    return result;
}

#endif