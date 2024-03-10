#include <iostream>

using namespace std;

int main (){
    int m, n, count;
    cin >> m >> n;
    int row, column;
    int arr[10][10];
    // nhap du lieu
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            char check; 
            cin >> check;
            if(check == '*') arr[i][j] = -1;
            else arr[i][j] = 0;
        }
    }
    //dem min
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
             count = 0;
            for(int a = -1; a <= 1; a++){
                for(int b = -1; b <= 1; b++){
                    row = i + a;
                    column = j + b;
                    if(row >= 0 && row < m && column >= 0 && column < n && arr[row][column] == -1) count++;
                }
            }
            if(arr[i][j] != -1) arr[i][j] = count;
        }
    }
    //in ra mh
    for(int i = 0; i < m; i++){
    	for(int j = 0; j < n; j++){
    		if(arr[i][j] == -1) cout << "*" << " ";
    		else cout << arr[i][j] << " ";
    	}
    	cout << endl;
    }
    return 0;
}