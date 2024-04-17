//tuan 2 bai 5c
#include<iostream>

using namespace std;

int number;

int main(){
	int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        for(int j = i; j <= n + i - 1; j++) cout << (j % 10 ? j % 10 : j) << " ";
        cout << endl;
    }
    return 0;
}