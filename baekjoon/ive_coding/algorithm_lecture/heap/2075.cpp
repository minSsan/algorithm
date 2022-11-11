#include <iostream>
#include <queue>

using namespace std;

int main() {
    int n;
    int nums[n][n];

    priority_queue<int> pq;
    // 첫 번째 최대 값 : 마지막 줄에 있는 수
    // 두 번째 최대 값 : ...
    

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> nums[i][j];
        }
    }

    return 0;
}