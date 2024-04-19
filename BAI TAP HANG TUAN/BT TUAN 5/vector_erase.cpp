#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N;
    cin >> N;
    vector<int> v;
    for(int i = 0; i < N; i++){
        int value;
        cin >> value;
        v.push_back(value);
    }
    int x, a, b;
    cin >> x >> a >> b;
    v.erase(v.begin() + x - 1);
    v.erase(v.begin() + a -1, v.begin() + b - 1);
    cout << v.size() << endl;
    for(int i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }
    return 0;
}
