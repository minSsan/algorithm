#include <iostream>
#include <queue>
#include <vector>

using namespace std;

queue<int> q;

const int MAX = 100000;
int prev_loc[100001]; // 인덱스 값의 위치를 방문하기 전에 거쳐온 위치를 저장
bool visited[100001];

void bfs(int start, int end) {
    prev_loc[start] = -1;
    q.push(start);

    while (!q.empty()) {
        int now = q.front();
        q.pop();

        if (now == end) {
            return ;
        }

        if (now + 1 <= MAX && prev_loc[now + 1] == 0 && !visited[now + 1]) {
            prev_loc[now + 1] = now;
            visited[now + 1] = true;
            q.push(now + 1);
        }

        if (now - 1 >= 0 && prev_loc[now - 1] == 0 && !visited[now - 1]) {
            prev_loc[now - 1] = now;
            visited[now - 1] = true;
            q.push(now - 1);
        }

        if (2 * now <= MAX && prev_loc[2 * now] == 0 && !visited[2 * now]) {
            prev_loc[2 * now] = now;
            visited[2 * now] = true;
            q.push(2 * now);
        }
    }
}

int main() {
    int n, k;
    cin >> n >> k;

    bfs(n, k);

    vector<int> s;
    int index = k;
    int cnt = 0;
    while (index != -1) {
        cnt++;
        s.push_back(index);
        index = prev_loc[index];
    }

    cout << --cnt << '\n';
    
    for (int i = s.size() - 1; i >= 0; --i) {
        cout << s[i] << ' ';
    }

    cout << '\n';
    
    return 0;
}