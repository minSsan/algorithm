#include <iostream>
#include <queue>

using namespace std;

// * 순간이동은 0초만에 이동이 가능하기 때문에, 도착 지점에 더 빨리 도착한다고 해서 최소 이동 횟수를 보장할 수 없다.
// * BFS로 도착 지점에는 더 빨리 도착하더라도, 비용(횟수)은 더 많이 들 수 있기 때문이다.
// 앞에서 풀었던 숨바꼭질 문제같은 경우에는, 어느 이동방향이던 비용이 1씩 똑같이 증가했기 때문에 
// 일찍 도착하면 최소 이동 횟수를 보장할 수 있었다.
// ? 따라서, 앞서 이미 방문했더라도 기록되어있는 방문 횟수보다 현재 방문 횟수가 더 적으면 방문 횟수를 새로 갱신한다.
// ? visited 사용 X, 전에 방문했더라도 최소 횟수인지 확인해야하기 때문.

int n, k;
const int MAX = 100000;

int bfs(int start) {
    int cnt[100001];
    queue<int> q;
    
    // ? cnt[100001] = {2000000000}; 안 됨
    for (int i = 0; i < 100001; ++i) {
        cnt[i] = 2000000000;
    }
    
    q.push(start);
    cnt[start] = 0;

    while (!q.empty()) {
        int now = q.front();
        q.pop();

        if (now == k) return cnt[k];

        // ? 이미 저장되어 있는 값보다 적은 횟수로 이동 가능하다면
        if (now - 1 >= 0 && cnt[now-1] > cnt[now] + 1) {
            cnt[now-1] = cnt[now] + 1; // 값을 갱신
            q.push(now-1); // 갱신한 상태로 다시 탐색한다
        }

        if (now + 1 <= MAX && cnt[now+1] > cnt[now] + 1) {
            cnt[now+1] = cnt[now] + 1;
            q.push(now+1);
        }

        if (2 * now <= MAX && cnt[2*now] > cnt[now]) {
            cnt[2*now] = cnt[now];
            q.push(2*now);
        }
    }
}

int main() {
    cin >> n >> k;

    cout << bfs(n) << '\n';

    return 0;
}