#include<bits/stdc++.h>
using namespace std;

struct Point{
    int x, y;
};

void Print(Point p){
    cout << p.x << " " << p.y;
}

int main(){
    Point point;
    point.x = 20;
    point.y = 10;
    Print(point);
    return 0;
}