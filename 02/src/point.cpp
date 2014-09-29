#include "point.h"


point::point(int x, int y) 
    : x(x), y(y) {}

point::point() {}

point point::operator-(point const & other) const {
    return point(x - other.x, y - other.y);
}

point point::operator+(point const & other) const {
    return point(x + other.x, y + other.y);
}

bool point::operator==(point const & other) const {
    return x == other.x && y == other.y;
}

bool point::operator<(point const & other) const {
    return (x == other.x) ? y < other.y : x < other.x;
}

int64_t point::cross(point const & other) const {
    return (int64_t)x * other.y - (int64_t)y * other.x;
}

int64_t point::dot(point const & other) const {
    return (int64_t)x * other.x + (int64_t)y * other.y;
}

std::istream& operator>>(std::istream& is, point & p) {
    char tmp;

    is >> tmp >> p.x >> tmp >> p.y >> tmp;
    return is;
}

