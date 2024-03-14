#include <iostream>

using namespace std;
bool check(const int &n){
	int m = 0, kt = n;
	while(kt != 0){
		m = (m + kt % 10) * 10;
		kt /= 10;
	}
	m /= 10;
	if(m == n) return true;
	return false;
}

int _count(const int &a, const int &b){
	int count = 0;
	for(int i = a; i <= b; i++){
		if(check(i)) count++;
	}
	return count;
}


int main (){	
	
	int T;
	cin >> T;
	for(int i = 0; i < T; i++){
		int a, b;
		cin >> a >> b;
		cout << _count(a,b) << endl;
	}
	return 0;	
}