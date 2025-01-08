#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

// 시작 시간과 종료 시간이 빠른 것을 먼저 진행하는 것이 적은 강의실 사용을 보장할 수 있다.

int main() {
    int n;
    cin >> n;

    pair<int, int> times[n];
    for (int i = 0; i < n; ++i) {
        cin >> times[i].first >> times[i].second;
    }

    sort(times, times + n);

    priority_queue<int, vector<int>, greater<int>> pq; // 각 강의실의 마지막 강의 종료 시간
    pq.push(times[0].second);

    for (int i = 1; i < n; ++i) {
        int last = pq.top();
        if (times[i].first >= last) {
            pq.pop();
        }
        pq.push(times[i].second);
    }

    cout << pq.size() << '\n';

    return 0;
}