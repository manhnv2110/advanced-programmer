#include <iostream>

using namespace std;

int main (){
	
	int n, count = 1, a= 1;
	cin >> n;
	while(a <= n){
		int i = a;
		for(int i = count; i <= n; i++){
			cout << i << " "; 
		}
		for(int j = 1; j < count; j++){
			cout << j << " ";
		}
		cout << endl;
		count++;
		a++;
	}
	return 0;
}