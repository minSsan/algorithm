#include <iostream>
#include <queue>

using namespace std;

// * 좌표를 압축한 결과 -> 해당 좌표보다 값이 작은 서로 다른 좌표의 수 (중복 X)
// ! n의 범위로 보아 브루트포스 사용 불가

int main() {
    int n;
    cin >> n;

    int inputs[n];
    // ? 최소 힙
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    for (int i = 0; i < n; ++i) {
        cin >> inputs[i];
        pq.push({inputs[i], i});
    }

    int cnt = 0;
    int result[n];

    while (!pq.empty()) {
        int temp = pq.top().first;
        while (!pq.empty() && pq.top().first == temp) {
            result[pq.top().second] = cnt;
            pq.pop();
        }
        cnt++;
    }

    for (int i = 0; i < n; ++i) {
        cout << result[i] << ' ';
    }

    cout << '\n';
    // 1000 999 1000 999 1000 999
    // 1000 1000 1000
    // temp = 1000, cnt = 1
    // * result
    // 1 0 1 0 1 0
    
    return 0;
}