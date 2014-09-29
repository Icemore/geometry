#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

#include "point.h"
#include "util.h"

using std::make_pair;

struct triangle {
    int i, j, k;
    
    triangle() {}
    triangle(int a, int b, int c) 
        : i(a), j(b), k(c) 
    {
        if(j < std::min(i, k)) {
            std::swap(i, j);
            std::swap(j, k);
        } else if(k < std::min(i, j)) {
            std::swap(i, k);
            std::swap(j, k);
        }
    }
};

std::ostream& operator<<(std::ostream& os, triangle const & t) {
    os << '(' << t.i << ", " << t.j << ", " << t.k <<  ')';
    return os;
}

void read(std::vector<point> & vec) {
    vec.clear();

    size_t n;
    std::cin >> n;

    for(size_t i = 0; i < n; ++i) {
        point p;
        std::cin >> p;
        vec.push_back(p);
    }
}

void print(std::vector<triangle> const & res) {
    for(triangle const & t : res) {
        std::cout << t << std::endl;
    }
}

class triangulator {
public: 
    triangulator(std::vector<point> const & poly) : poly(poly) {}

    std::vector<triangle> triangulate() {
        result.clear();
        while(!st.empty()) st.pop();


        st.push(make_pair(-1, 0));

        int lower = 1;
        int upper = (int)poly.size() - 1;
        while(lower != upper) {
            int cur = poly[lower] < poly[upper] ? lower++ : upper--;
            
            if(adjacent(cur, st.top().second)) {
                while(st.top().first != -1 && 
                      CCW(poly[st.top().first], poly[st.top().second], poly[cur]) < 0) {
                    addTriangleFromStack(cur); 
                    st.pop();
                } 

                st.push(make_pair(st.top().second, cur));
            }
            else {
                int last = st.top().second;
                addAllStackTriangles(cur);
                st.push(make_pair(-1, last));
                st.push(make_pair(last, cur));
            }
        }

        addAllStackTriangles(lower);

        return result;
    }

private:
    bool adjacent(size_t i, size_t j) {
        return ((i + 1) % poly.size() == j) || ((j + 1) % poly.size() == i);
    }

    void addTriangle(int t1, int t2, int t3) {
        if(CCW(poly[t1], poly[t2], poly[t3]) < 0) {
            std::swap(t1, t3);
        }
        result.push_back(triangle(t1, t2, t3));
    }

    void addTriangleFromStack(int t3) {
        addTriangle(st.top().first, st.top().second, t3);
    }
    
    void addAllStackTriangles(int t3) {
        while(st.top().first != -1) {
            addTriangleFromStack(t3);
            st.pop();
        }
        st.pop();
    }

    std::stack<std::pair<int, int>> st;
    std::vector<triangle> result;
    std::vector<point> const & poly;
};

int main() {
    std::vector<point> vec;
    read(vec);
    
    triangulator solver(vec);
    print(solver.triangulate());


    return 0;
}
