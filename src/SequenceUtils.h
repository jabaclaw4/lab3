#ifndef SEQUENCE_UTILS_H
#define SEQUENCE_UTILS_H

#include <iostream>
#include "Sequence.h"
template <class T>
std::ostream& operator<<(std::ostream& os, const Sequence<T>& seq) {
    os << "[";
    for (int i = 0; i < seq.GetLength(); i++) {
        os << seq[i];
        if (i < seq.GetLength() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

#endif