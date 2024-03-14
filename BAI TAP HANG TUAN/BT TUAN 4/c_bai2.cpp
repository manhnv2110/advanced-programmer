//bai 2: xau doi xung
#include <iostream>
#include <string>

using namespace std;

bool check(const string &str){
	
	string _s;
	for(int i = str.length() - 1; i != -1; i--){
		_s += str[i];
	}
	if(_s == str) return true;
	return false;
	
}

int main (){
	
	string s;
	cin >> s;
	if(check(s)) {
		cout << "YES";
	}
	else 
	cout << "NO";
	return 0;
}