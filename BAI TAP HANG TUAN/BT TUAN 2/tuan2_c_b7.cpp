#include <iostream>
using namespace std;

bool check(int truoc, int sau){
	if(sau != truoc) return true;
	return false;
}

int main (){
	int a;
	cin >> a;
	int n = a;
	if(a >= 0){
	cout << a << " ";
	while (n >= 0){
		int m = n;
		cin >> n;
		if(n < 0) break;
		if(check(m,n)) cout << n << " ";
	}
}
	return 0;
}