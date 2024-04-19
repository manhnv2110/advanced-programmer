#include <iostream>

// Dear teacher, I haven't been able to complete the Tower of Hanoi exercise yet
using namespace std;

int *arr;

int max(int const &a, int const &b){
	if(a > b) return a;
	return b;
}

int dequy(int n){
	int value = 0;
	for(int i = 1; i <= n; i++){
		value = max(value, arr[i] + dequy(n-i));
	}
	return value;
}

int main (){
	int n; cin >> n;
	arr = new int[n];
	arr[n] = {};
	for(int i = 1; i <= n; i++){
		cin >> arr[i];
	}
	cout << dequy(n);
	delete[] arr;
	return 0;
}