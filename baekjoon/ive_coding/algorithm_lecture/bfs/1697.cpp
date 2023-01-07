#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int n, k;
int cnt[100001];
const int MAX = 100000;

queue<int> q;

int now, next_num;

void bfs() {
    while (!q.empty() && q.front() != k) {
        now = q.front();
        q.pop();

        next_num = now + 1;
        if (next_num <= MAX && cnt[next_num] == 0) {
            q.push(next_num);
            cnt[next_num] = cnt[now] + 1;
        }
        next_num = now - 1;
        if (next_num >= 0 && cnt[next_num] == 0) {
            q.push(next_num);
            cnt[next_num] = cnt[now] + 1;
        }
        next_num = 2 * now;
        if (next_num <= MAX && cnt[next_num] == 0) {
            q.push(next_num);
            cnt[next_num] = cnt[now] + 1;
        }
    }
}

int main() {
    cin >> n >> k;

    q.push(n);

    bfs();

    cout << cnt[k] << '\n';

    return 0;
}