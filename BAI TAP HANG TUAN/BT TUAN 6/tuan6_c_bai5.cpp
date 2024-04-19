#include <iostream>
using namespace std;

int isPrime(int n) {
    if (n <= 1) {
        return 0; 
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0; 
        }
    }
    return 1; 
}


void printPrimes(int N) {
    for (int i = 2; i < N; i++) {
        if (isPrime(i)) {
            cout << i << " ";
        }
    }
}

int main() {
    int N;
    cin >> N;
    printPrimes(N);
    return 0;
}
