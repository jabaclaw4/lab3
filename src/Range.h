#ifndef RANGE_H
#define RANGE_H

#include "MutableArraySequence.h"

Sequence<int>* Range(int l, int h) {
    auto* seq = new MutableArraySequence<int>();

    for (int i = l; i <= h; i++) {
        seq->Append(i);
    }
    return seq;
}

#endif