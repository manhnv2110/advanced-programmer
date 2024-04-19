#include <iostream>
using namespace std;

struct Point {
    int x, y;
};


struct Rect {
    int x, y; 
    int w, h; 
    bool contains(const Point& p) const {
        return (p.x >= x && p.x <= x + w && p.y >= y && p.y <= y + h);
    }
};

int main() {
    Rect rectangle = {2, 2, 6, 4};
    Point point1 = {4, 3};
    Point point2 = {8, 6};

    return 0;
}
