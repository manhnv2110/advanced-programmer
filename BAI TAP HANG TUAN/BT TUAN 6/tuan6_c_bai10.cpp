#include <iostream>
#include <cstdlib> 
#include <ctime>  

using namespace std;

void taoMangNgauNhien(int arr[], int N) {
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 50; 
    }
}


void inBo3TongChiaHetCho25(int arr[], int N) {
    for (int i = 0; i < N - 2; ++i) {
        for (int j = i + 1; j < N - 1; ++j) {
            for (int k = j + 1; k < N; ++k) {
                if ((arr[i] + arr[j] + arr[k]) % 25 == 0) {
                    std::cout << arr[i] << " " << arr[j] << " " << arr[k] <<endl;
                }
            }
        }
    }
}

int main() {
	int N;
	cin >> N;
    int arr[N];

    srand(time(NULL));

    taoMangNgauNhien(arr, N);

    inBo3TongChiaHetCho25(arr, N);

    return 0;
}
