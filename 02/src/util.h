#pragma once
#include "point.h"

int CCW(point const & p1, point const & p2, point const & p3);

template<class T>
int sign(T val) {
    return (T(0) < val) - (val < T(0));
}
