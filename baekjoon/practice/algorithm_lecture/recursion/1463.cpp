#include <iostream>

using namespace std;

const int MAXIMUM_NUM = 2100000000;

int min_count = MAXIMUM_NUM;

void min_calc(int n, int count) { // 10, 0 | 5, 1 | 4, 2
    if (n == 1) {
        if (count < min_count) {
            min_count = count;
        }
        // return min_count;
        return ;
    }
    if (n % 3 == 0){
        min_calc(n / 3, count + 1);
    }
    if (n % 2 == 0) {
        min_calc(n / 2, count + 1); // 5, 1
    }
    min_calc(n - 1, count + 1); // 4, 2
}

int main() {
    int N;
    cin >> N;
    min_calc(N, 0);
    cout << min_count << '\n';
    // cout << min_calc(N, 0) << '\n';
    return 0;
}