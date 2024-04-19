#include <iostream>
using namespace std;

struct Point{
    int i, j;
    Point(){};
    Point(int _i, int _j){
        i = _i;
        j = _j;
    }

    void printPoint(){
        cout << i << " " << j << endl;
    }
};

struct Rect{
    int x, y, w, h;
    Rect(){};
    Rect(int _x, int _y, int _w, int _h){
        x = _x;
        y = _y;
        w = _w;
        h = _h;
    }

    void printRect(){
        cout << "[x, y, width, height]: " << "[" << x << ", " << y << ", " << w << ", " << h << "]" << endl;
    }

    bool contains(const Point& a){
        if((x <= a.i && a.i <= x+w) && (y <= a.j && a.j <= y+h)) return true;
        else return false;
    }
};

struct Ship{
    string id;
    Rect rect;
    int dx, dy;

    Ship(){};
    Ship(string _id, Rect _rect, int _dx, int _dy){
        id = _id;

        rect.x = _rect.x;
        rect.y = _rect.y;
        rect.w = _rect.w;
        rect.h = _rect.h;

        dx = _dx;
        dy = _dy;
    }

    void move(){
        rect.x += dx;
        rect.y += dy;
    }
};

void display(Ship& ship){
    cout << "id: " << ship.id << endl;
    ship.rect.printRect();
    cout << "dx = " << ship.dx << endl;
    cout << "dy = " << ship.dy << endl;
}

int main(){
    Ship ship{"ok", {1, 6, 4, 2}, 3, 5};
    display(ship);
    return 0;
}