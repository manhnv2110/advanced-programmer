#include <iostream>
#include <string>
using namespace std;

struct Tau {
    string ten;
    int x, y; 
    int toc_do; 

    void di_chuyen() {
        x += toc_do;
        y += toc_do; 
    }
};

void hien_thi(const Tau& tau) {
    cout << "Tau " << tau.ten << " tai vi tri (" << tau.x << ", " << tau.y << ")" <<endl;
}

int main() {
    Tau tau1 = {"Tau1", 0, 0, 1};
    Tau tau2 = {"Tau2", 5, 10, 2};

    int vong_lap = 0;
    while (vong_lap < 10) {
        tau1.di_chuyen();
        tau2.di_chuyen();
        hien_thi(tau1);
        hien_thi(tau2);
        vong_lap++;
    }

    return 0;
}
