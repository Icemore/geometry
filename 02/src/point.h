#pragma once
#include <istream>

struct point {
    int x;
    int y;

    point(int x, int y);
    point();

    point operator-(point const & other) const;
    point operator+(point const & other) const;
    bool operator==(point const & other) const;
    bool operator<(point const & other) const;

    int64_t cross(point const & other) const;
    int64_t dot(point const & other) const;
};

std::istream& operator>>(std::istream& is, point & p);
