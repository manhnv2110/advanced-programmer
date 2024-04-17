#include <iostream>
using namespace std;

int main(){
	int n, m, a[107][107], count = 1;
	cin >> m >> n;
	int dong = m, cot = n, k = 1, p = 0;
	while(k <= m*n){
		for(int i = p; i < cot; i++)     a[p][i] = k++;
		for(int i = p+1; i < dong; i++)  a[i][cot-1] = k++;
		for(int i = cot-2; i >=p; i--)   a[dong-1][i] = k++;
		for(int i = dong-2; i > p; i--)  a[i][p] = k++;
		p++;
        dong--; 
        cot--;
	}

	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			cout << a[i][j] << " ";
        }
        cout << endl;
	}
    return 0;
}