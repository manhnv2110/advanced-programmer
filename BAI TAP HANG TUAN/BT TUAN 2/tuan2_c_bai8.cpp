#include <iostream>
#include <cmath>

using namespace std;

int main(){
    double a, b, c;
    cin >> a >> b >> c;
    double delta = b*b - 4*a*c;
    if(delta > 0){
        cout << "Phuong trinh co 2 nghiem phan biet la: " << endl;
        cout << "x1 = " << (double)(-b + sqrt(delta))/2.0*a << endl;
        cout << "x2 = " << (double)(-b - sqrt(delta))/2.0*a << endl;
    }
    else if(delta == 0){
        cout << "Phuong trinh co nghiem kep la: " << endl;
        cout << "x = " << (double)(-b/2.0*a) << endl;
    }
    else{
        cout << "Phuong trinh co 2 nghiem phuc la: " << endl;
        cout << "x1 = " << (double)(-b/(2.0*a)) << " + " << (double)sqrt(-delta)/(2.0*a) << "i" << endl;
        cout << "x2 = " << (double)(-b/(2.0*a)) << " - " << (double)sqrt(-delta)/(2.0*a) << "i" << endl;
    }
    return 0;
}