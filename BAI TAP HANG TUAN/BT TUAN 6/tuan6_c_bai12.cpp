#include <iostream>
using namespace std;

int giaiThua(int n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return n * giaiThua(n - 1);
}


int toHop(int k, int n) {
    return giaiThua(n) / (giaiThua(k) * giaiThua(n - k));
}


int kiemTra(int k, int n) {
    if (k >= 0 && k <= n && n >= 1 && n <= 20)
        return 1;
    else
        return 0;
}


void nhapKN(int k[], int n[], int *soPhanTu) {
    *soPhanTu = 0;
    int kiemTraK, kiemTraN;
    do {
        cin >> k[*soPhanTu] >> n[*soPhanTu];
        kiemTraK = kiemTra(k[*soPhanTu], n[*soPhanTu]);
        if (k[*soPhanTu] != -1 || n[*soPhanTu] != -1) {
            (*soPhanTu)++;
        }
    } while (k[*soPhanTu - 1] != -1 || n[*soPhanTu - 1] != -1);
}

int main() {
    int k[100], n[100]; 
    int soPhanTu;


    nhapKN(k, n, &soPhanTu);


    for (int i = 0; i < soPhanTu; ++i) {
        if (k[i] == -1 && n[i] == -1)
            break;
        if (kiemTra(k[i], n[i]))
            cout << toHop(k[i], n[i]) << endl;
    }

    return 0;
}
