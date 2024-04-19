//b6
#include <iostream>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

bool areCoprime(int a, int b) {
    return gcd(a, b) == 1;
}

int main() {
    int a, b;
    cin >> a >> b;

    int value = gcd(a, b);
    cout << value << endl;
    if (areCoprime(a, b)) {
       cout << a << " va " << b << " la 2 so nguyen to cung nhau." << endl;
    } else {
        cout << a << " va " << b << " khong la 2 so nguyen to cung nhau." << endl;
    }

    return 0;
}
