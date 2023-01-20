#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int n, k;
int cnt[100001];
bool visited[100001];
bool isFound;
int min_result; // 최소 경로 수
int min_cnt; // 경우의 수 카운트
const int MAX = 100000;

struct node
{
    int position; // 노드의 번호
    int cnt; // 노드를 방문하는 데까지 이동한 경로
};
queue<node> q;

int now_pos, now_cnt;


void bfs() {
    while (!q.empty()) {
        now_pos = q.front().position;
        now_cnt = q.front().cnt;

        visited[now_pos] = true;
        q.pop();

        if (now_pos == k) {
            min_result = now_cnt;
            min_cnt++;
            return ;
        }

        if (now_pos + 1 <= MAX && !visited[now_pos + 1]) {
            q.push({now_pos + 1, now_cnt + 1});
        }
        
        if (now_pos - 1 >= 0 && !visited[now_pos - 1]) {
            q.push({now_pos - 1, now_cnt + 1});
        }
        
        if (2 * now_pos <= MAX && !visited[2 * now_pos]) {
            q.push({2 * now_pos, now_cnt + 1});
        }
    }
}

int main() {
    cin >> n >> k;

    q.push({n, 0});

    bfs();

    while (!q.empty()) {
        now_pos = q.front().position;
        now_cnt = q.front().cnt;
        q.pop();

        if (now_pos == k && now_cnt == min_result) {
            min_cnt++;
        }
    }

    cout << min_result << '\n';
    cout << min_cnt << '\n';

    return 0;
}