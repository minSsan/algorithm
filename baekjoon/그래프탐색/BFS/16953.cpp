#include <iostream>
#include <queue>

using namespace std;

long long a, b;

int bfs() {
    queue<pair<int, int>> q; // {num, cnt}
    q.push({a, 1});

    while (!q.empty()) {
        long long cur = q.front().first;
        int cnt = q.front().second;
        q.pop();

        if (cur == b) {
            return cnt;
        }
        if (cur > b) {
            continue;
        }

        if (cur * 2 <= b) q.push({cur * 2, cnt+1});
        if (cur * 10 + 1 <= b) q.push({cur * 10 + 1, cnt+1});
    }

    return -1;
}

int main() {
    cin >> a >> b;

    cout << bfs() << '\n';

    return 0;
}