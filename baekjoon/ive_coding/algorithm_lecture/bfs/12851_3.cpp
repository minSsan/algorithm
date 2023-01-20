#include <iostream>
#include <queue>

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

void bfs(int start) {
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int now = q.front();
        visited[now] = true;
        q.pop();
        cout << "now: " << now << '\n';

        if (now == k) {
            cout << "cnt[k]: " << cnt[k] << '\n';
            if (!isFound) { // ? 아직 최소 경로를 찾기 전이라면,
                isFound = true; // ? 최소값 찾음 표시 남기기
                min_result = cnt[k]; // ? 최소 경로 수 저장
                min_cnt = 1;
            } 
            visited[k] = false; // ? 다른 경로도 찾기 위해서 방문처리 해제
        } 

        if (now - 1 >= 0 && !visited[now - 1]) {
            if (!isFound) { // ? 아직 최소값이 발견되지 않았다면
                cnt[now - 1] = cnt[now] + 1;
                q.push(now - 1);
            } else if (now - 1 == k) { // ? 최소값이 발견된 상태고, now - 1 값이 k라면,
                if (cnt[now] + 1 == min_result) {
                    min_cnt++;
                }
            }
        }

        if (now + 1 <= MAX && !visited[now + 1]) {
            if (!isFound) { // 아직 최소값이 발견되지 않았다면
                cnt[now + 1] = cnt[now] + 1;
                q.push(now + 1);
                
            } else if (now + 1 == k) {
                if (cnt[now] + 1 == min_result) {
                    min_cnt++;
                }
            }
        }

        if (2 * now <= MAX && !visited[2 * now]) {
            if (!isFound) { // 아직 최소값이 발견되지 않았다면
                cnt[2 * now] = cnt[now] + 1;
                q.push(2 * now);
                
            } else if (2 * now == k) {
                if (cnt[now] + 1 == min_result) {
                    min_cnt++;
                }
            }
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