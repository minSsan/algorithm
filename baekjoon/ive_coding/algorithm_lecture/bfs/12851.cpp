#include <iostream>
#include <queue>

using namespace std;

const int MAX = 100000;

int n, k;
int cnt[100001];
int visited[100001];
int min_result, min_cnt;
queue<int> q;

void bfs(int start) {
    q.push(start);

    while (!q.empty()) {
        int now = q.front();
        q.pop();

        if (now == k) {
            if (min_result == 0) {
                min_result = cnt[k];
                min_cnt++;
            } else if (cnt[k] == min_result) {
                min_cnt++;
            }
        }

        int next_num = now + 1;
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

    bfs(n);

    cout << min_result << '\n';
    cout << min_cnt << '\n';

    return 0;
}