#include <iostream>
#include <queue>
#include <algorithm>
#define INF 123456789

using namespace std;

// * 어떤 버튼이 고장났는지 주어졌을 때, 채널 N으로 이동하기 위해서 버튼을 최소 몇 번 눌러야 하는가?
// * 지금 보고 있는 채널은 100번이다.

int n, m; // n: 이동하고자 하는 채널 번호, m: 고장난 버튼 수
bool available[10]; // 0 ~ 9까지의 버튼이 사용 가능한지
bool visited[INF];

// ? 1. 시작 번호를 정해야 한다. -> N과 최대한 가까운 번호를 찾아야 함.
// ? 2. 작동 가능한 숫자 조합으로 N과 가장 가까운 숫자를 찾았다면, 정답 = 시작 번호의 길이 + |N-시작번호|
// ! 시작 번호를 어떻게 정할 것인지?
// - N에서 숫자를 하나씩 더하거나 빼면서, 각 자릿수 숫자들이 모두 작동 가능한지 확인한다.
// - BFS로 탐색

// ? 각 자릿수가 모두 리모컨으로 입력 가능한 숫자인지 확인하는 함수
bool check(int num) {
    if (num == 0) {
        return available[0];
    }
    
    int tmp;
    while (num > 0) {
        tmp = num % 10;
        num = num / 10;
        if (!available[tmp]) {
            return false;
        }
    }
    return true;
}

int num_len(int num) {
    if (num == 0) return 1;
    
    int cnt = 0;
    while (num > 0) {
        num = num / 10;
        cnt++;
    }
    return cnt;
}

int bfs(int now) {
    queue<pair<int, int>> q; // {현재 채널 번호, cnt}
    q.push({now, 0});
    visited[now] = true;

    while (!q.empty()) {
        int now = q.front().first;
        int cnt = q.front().second;
        q.pop();
        
        if (check(now)) { // 현재 숫자의 모든 자릿수가 입력 가능한 번호라면,
            cout << "now: " << now << '\n';
            return cnt + num_len(now);
        }

        if (now + 1 <= INF && !visited[now+1]) {
            q.push({now + 1, cnt + 1});
            visited[now+1] = true;
        }

        if (now - 1 >= 0 && !visited[now-1]){
            q.push({now - 1, cnt + 1});
            visited[now-1] = true;
        }
    }
}

int main() {
    // 사용 가능한 번호 초기화
    for (int i = 0; i < 10; ++i) {
        available[i] = true;
    }

    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int num; // 고장난 번호
        cin >> num;
        available[num] = false;
    }

    if (n == 100) {
        cout << 0 << '\n';
    } else {
        cout << min(bfs(n), abs(n - 100)) << '\n';
    }

    return 0;
}