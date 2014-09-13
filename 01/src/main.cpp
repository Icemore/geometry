#include <vector>
#include <iostream>

/* 
 * Determines whether a point is inside a polygon
 * by shooting a ray at the (1, 0) direction and calculating the parity of
 * intersections
 */

struct point {
    int x;
    int y;

    point(int x, int y) 
        : x(x), y(y) {}

    point() {}

    point operator-(point const & other) {
        point res(x - other.x, y - other.y);
        return res;
    }

    int cross(point const & other) {
        return x * other.y - y * other.x;
    }

    bool operator==(point const & other) {
        return x == other.x && y == other.y;
    }
};

std::istream& operator>>(std::istream& is, point & p) {
    char tmp;

    is >> tmp >> p.x >> tmp >> p.y >> tmp;
    return is;
}

class polygon {
public:
    void read() {
        poly.clear();

        size_t n;
        std::cin >> n;

        for(size_t i = 0; i < n; ++i) {
            point p;
            std::cin >> p;
            
            // discard middle point if three poins in a row lying on the same horizontal line
            if(poly.size() > 1 && 
                    isOnHorizontalLine(poly[poly.size() - 2], poly[poly.size() - 1], p)) {
                poly.pop_back();
            }

            poly.push_back(p);
        }
        
        // check three wrapping points [n-2] [n-1] [0]
        if(isOnHorizontalLine(poly[poly.size() - 2], poly[poly.size() - 1], poly[0])) {
            poly.pop_back();
        }

        // check three wrapping points [n-1] [0] [1]
        if(isOnHorizontalLine(poly.back(), poly[0], poly[1])) {
            poly[0] = poly.back();
            poly.pop_back();
        }
    }
    
    bool isInside(point p) {
        int intersectCount = 0;

        for(int i = 0; i < (int)poly.size(); ++i) {
            int cur = checkForEdge(p, i, (i + 1) % poly.size());
            
            // if point lies on the boundary return no
            if(cur == -1) {
                return false;
            }
            else {
                intersectCount += cur;
            }
        }

        return intersectCount % 2;
    }

private:
    bool isOnHorizontalLine(point const & p1, point const & p2, point const & p3) {
        return (p1.y == p2.y && p2.y == p3.y);
    }

    int sign(int val) {
       return (0 < val) - (val < 0);
    }

    int checkForEdge(point p, int i, int j) {
        if(p == poly[i] || p == poly[j]) {
            return -1;
        }

        // if the edge lies on the line of the ray
        if(isOnHorizontalLine(p, poly[i], poly[j])) {
            // the edge lies to the left from p and does not touch the ray
            if(std::max(poly[i].x, poly[j].x) < p.x) {
                return 0;
            }
            
            // the edge lies to the right from p and completely covered by the ray
            if(std::min(poly[i].x, poly[j].x) > p.x) {
                return neighbourCheck(p, i - 1, j + 1);
            }
            
            // p lies inside the edge
            return -1;
        }

        // check if the edge touches the ray with one end
        if(p.y == poly[i].y && p.x < poly[i].x) {
            return neighbourCheck(p, i - 1, j);
        }
        // if the second end touches the ray just skip it. 
        // it will be processed with the next edge
        if(p.y == poly[j].y && p.x < poly[j].x) {
            return 0;
        }

        // finaly check for intersection
        return doesIntersects(p, poly[i], poly[j]);
    }

    int doesIntersects(point p, point r1, point r2) {
        // make sure r1.y < r2.y
        if(r1.y > r2.y) {
            std::swap(r1, r2);
        }
        
        // make sure r1.y < p.y < r2.y
        if(!(r1.y < p.y && p.y < r2.y)) {
            return 0;
        }
        
        // check for intersection
        int t = (r2 - p).cross(r2 - r1);
        
        // if point lies on the edge
        if(t == 0) {
            return -1;
        }

        return t > 0 ? 1 : 0;
    }

    int neighbourCheck(point p, int i, int j) {
        i = (i + poly.size()) % poly.size();
        j = (j + poly.size()) % poly.size();

        int dy1 = sign(p.y - poly[i].y);
        int dy2 = sign(p.y - poly[j].y);
        
        return dy1 * dy2 < 0 ? 1 : 0;
    }

    std::vector<point> poly;
};

int main() {
    polygon poly;
    poly.read();
    
    int m;
    std::cin >> m;

    for(int i = 0; i < m; ++i) {
        point p;
        std::cin >> p;

        if(poly.isInside(p)) {
            std::cout << "yes" << std::endl;
        }
        else {
            std::cout << "no" << std::endl;
        }
    }

    return 0;
}
