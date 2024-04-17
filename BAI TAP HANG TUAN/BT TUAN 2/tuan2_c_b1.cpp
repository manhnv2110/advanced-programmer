// phan c bai 1
#include <iostream>
#include <cmath>

using namespace std;

int number;

bool Prime(int number){
    if(number < 2) return false;
    for(int i = 2; i <= sqrt(number); i++){
        if(number % i == 0) return false;
    }
    return true;
}

int main(){
    cin >> number;
    if(Prime(number)) cout << "yes";
    else cout << "no";
    return 0;
}