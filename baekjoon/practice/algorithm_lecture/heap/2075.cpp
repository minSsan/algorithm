#include <iostream>
#include <queue>

using namespace std;

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    int nums[n][n];

    priority_queue<pair<int, pair<int, int>>> pq;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> nums[i][j];
        }
    }

    for (int j = 0; j < n; ++j){
        pq.push({nums[n-1][j], {n-1, j}});
    }

    int row, col;
    for (int i = 0; i < n-1; ++i) {
        row = pq.top().second.first - 1;
        col = pq.top().second.second;
        pq.push({nums[row][col], {row, col}});
        pq.pop();
    }

    cout << nums[pq.top().second.first][pq.top().second.second] << '\n';

    return 0;
}