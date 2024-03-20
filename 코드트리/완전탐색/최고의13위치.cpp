#include <iostream>
#include <algorithm>

using namespace std;

//? 동전이 있는 곳: 1, 없는 곳: 0
//? 1 * 3 크기의 격자 안에 들어가는 최대 동전 수 구하기
int main() {
    int n;
    cin >> n;
    int v[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> v[i][j];
        }
    }
    int max_cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n-2; ++j) {
            max_cnt = max(max_cnt, v[i][j] + v[i][j+1] + v[i][j+2]);
        }
    }

    cout << max_cnt << '\n';

    return 0;
}