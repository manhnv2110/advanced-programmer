#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    int n, x;
    cin >> n;
    vector<int> vt;
    for(int i = 0; i < n; i++){
        cin >> x;
        vt.push_back(x);
    }  
    sort(vt.begin(), vt.end());
    for(int i = 0; i < n; i++) cout << vt[i] << " ";
    return 0;
}
