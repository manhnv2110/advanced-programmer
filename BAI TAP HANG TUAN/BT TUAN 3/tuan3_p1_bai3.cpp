#include <iostream>
using namespace std;

struct Point{
    int x, y;
};

void Print(Point p){
    cout << p.x << " "<< p.y;
}

Point mid_point(const Point &a, const Point &b){
    Point td;
    td.x = (a.x + b.x)/2;
    td.y = (a.y + b.y)/2;
    return td;
}

int main(){
    Point a, b;
    a.x = 40;
    a.y = 20;
    b.x = 10;
    b.y = 2;
    Print(mid_point(a, b));
    return 0;
}