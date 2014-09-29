#include "util.h"

#include <cstdint>

int CCW(point const & p1, point const & p2, point const & p3) {
    return sign(((int64_t)(p1.x - p3.x) * (p2.y - p1.y) + (int64_t)(p2.x - p1.x) * (p3.y - p1.y)));
}
