#include <cmath>
#include <set>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    set<int> s;
    int Q, y, x;
    cin >> Q;
    for(int i = 0; i < Q; i++){
        cin >> y;
        if(y == 1){
            cin >> x;
            s.insert(x);
        }
        if(y == 2){
            cin >> x;
            s.erase(x);
        }
        if(y == 3){
            cin >> x;
            set<int> :: iterator it = s.find(x);
            if(it == s.end()) {
                cout << "No" << endl;
            }
            else {
                cout << "Yes" << endl;
            }
        }
    }  
    return 0;
}
