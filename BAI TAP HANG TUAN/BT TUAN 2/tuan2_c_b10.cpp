//tuan2 c bai 10
#include <iostream>
#include <iomanip>

using namespace std;

int main(){
    cout << "Fahrenheit" << "     " << "Celcius" << "     " << "Absolute" << endl;
    for(int f = 0; f <= 300; f += 20){
        double c = (double)(f - 32) * (double)5.0/9.0;
        double k = c + 273.15;
        cout << f << "     ";
        cout << fixed << setprecision(2) << c << "     ";
        cout << fixed << setprecision(2) << k << endl;
    }
    return 0;
}