#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX = 100000;

int n, k;
queue<int> q;
int cnt[100001];
bool visited[100001];
bool isFound; // 최소 경로를 찾았는가?
int min_result; // 최소 경로 수
int min_cnt; // 최소 경로 수로 이동할 수 있는 경우의 수

// ? 최소 경로를 먼저 찾는다.
// ? 최소 경로를 찾았으면 isFound를 true로 변경하고, 그 뒤에 이어지는 가지는 푸시하지 X
// ! 방문 처리 시점에 따라서 방문 횟수가 달라진다.
// -> 만약 서로 다른 경로를 모두 구하는 경우에는, 큐에 푸시함과 동시에 방문 처리를 하면 안된다. 이 경우에는 큐에 pop하면서 방문처리를 해야 함
// -> 하지만 이런 특수한 경우가 아니라면 큐에 푸시함과 동시에 방문 처리를 하는 것이 일반적이다.
// -> 그렇지 않으면 이미 방문한 노드를 또 다시 큐에 푸시하기 때문에, 메모리 초과가 발생할 수 있다.

void bfs(int start) {
    q.push(start);
    visited[start] = true;
    cnt[start] = 0;

    while (!q.empty()) {
        int now = q.front();
        visited[now] = true;
        q.pop();
        cout << "now: " << now << '\n';

        if (now == k) {
            if (!isFound) {
                cout << "cnt[k]: " << cnt[k] << '\n';
                
                isFound = true; // ? 최소값 찾음 표시 남기기
                min_result = cnt[k]; // ? 최소 경로 수 저장
                min_cnt = 1;
                
                visited[k] = false; // ? 다른 경로도 찾기 위해서 방문처리 해제
            } else if (cnt[k] == min_result) {
                min_cnt++;
            }
        } 

        if (now - 1 >= 0 && !visited[now - 1]) {
            if (!isFound) { // ? 아직 최소값이 발견되지 않았다면
                cout << "now found" << '\n';
                cnt[now - 1] = min(cnt[now - 1], cnt[now] + 1);
                q.push(now - 1);
            } else {
                cnt[now - 1] = cnt[now] + 1;
            }
        }

        if (now + 1 <= MAX && !visited[now + 1]) {
            if (!isFound) { // 아직 최소값이 발견되지 않았다면
                cout << "now found" << '\n';
                cnt[now + 1] = min(cnt[now + 1], cnt[now] + 1);
                q.push(now + 1);  
            } else {
                cnt[now + 1] = cnt[now] + 1;
            }
        }

        if (2 * now <= MAX && !visited[2 * now]) {
            if (!isFound) { // 아직 최소값이 발견되지 않았다면
                cout << "now found" << '\n';
                cnt[2 * now] = min(cnt[2 * now], cnt[now] + 1);
                q.push(2 * now); 
            } else {
                cnt[2 * now] = cnt[now] + 1;
            }
        }
    }
}

int main() {
    cin >> n >> k;

    for (int i = 0; i < 100001; ++i) {
        cnt[i] = 100000;
    }

    bfs(n);

    cout << min_result << '\n';
    cout << min_cnt << '\n';

    return 0;
}