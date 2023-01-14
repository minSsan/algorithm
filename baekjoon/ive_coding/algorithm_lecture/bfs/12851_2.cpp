#include <iostream>
#include <queue>

using namespace std;

int n, k;
int cnt[100001];
const int MAX = 100000;


void bfs(int start) {
    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int now = q.front();
        q.pop();

        if (now == k) {
            return ;
        }

        if (now + 1 <= MAX && cnt[now + 1] == 0) {
            q.push(now + 1);
            cnt[now + 1] = cnt[now] + 1;
        }

        if (now - 1 >= 0 && cnt[now - 1] == 0) {
            q.push(now - 1);
            cnt[now - 1] = cnt[now] + 1;
        }

        if (2 * now <= MAX && cnt[2 * now] == 0) {
            q.push(2 * now);
            cnt[2 * now] = cnt[now] + 1;
        }
    }
}

void bfs2(int start) {
    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int now = q.front();
        q.pop();

        if (now == k) {
            return ;
        }

        if (now - 1 >= 0 && cnt[now - 1] == 0) {
            q.push(now - 1);
            cnt[now - 1] = cnt[now] + 1;
        }

        if (now + 1 <= MAX && cnt[now + 1] == 0) {
            q.push(now + 1);
            cnt[now + 1] = cnt[now] + 1;
        }

        if (2 * now <= MAX && cnt[2 * now] == 0) {
            q.push(2 * now);
            cnt[2 * now] = cnt[now] + 1;
        }
    }
}

void bfs3(int start) {
    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int now = q.front();
        q.pop();

        if (now == k) {
            return ;
        }

        if (2 * now <= MAX && cnt[2 * now] == 0) {
            q.push(2 * now);
            cnt[2 * now] = cnt[now] + 1;
        }

        if (now - 1 >= 0 && cnt[now - 1] == 0) {
            q.push(now - 1);
            cnt[now - 1] = cnt[now] + 1;
        }

        if (now + 1 <= MAX && cnt[now + 1] == 0) {
            q.push(now + 1);
            cnt[now + 1] = cnt[now] + 1;
        }

    }
}

int main() {
    cin >> n >> k;

    int min_cnt, result = 0;

    bfs(n);

    min_cnt = cnt[k];
    result++;

    cnt[k] = 0;

    bfs2(n);

    if (cnt[k] == min_cnt) {
        result++;
    }

    cnt[k] = 0;

    bfs3(n);

    if (cnt[k] == min_cnt) {
        result++;
    }

    cout << result << '\n';

    return 0;
}