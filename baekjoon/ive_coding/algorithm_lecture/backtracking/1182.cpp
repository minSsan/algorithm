#include <iostream>

using namespace std;

// * 합이 s가 되는 부분수열의 갯수

int n, s;
int seq[20];
int cnt;
bool visited[20];

// ? sum: 현재까지 만든 수열의 합, s_cnt: 수열의 길이
// ? index: 중복을 포함하지 않기 위해 추가한 변수 (그 다음 숫자를 추가하기 위한 seq 탐색 시작점)
void dfs(int sum, int s_cnt, int index) {
    if (s_cnt > 0 && sum == s) { // 만약 부분수열 합이 s라면,
        cnt++; // cnt 증가 
        // 함수 종료하면 안 됨. 종료하면 현재 숫자를 포함한 다른 조합을 더이상 확인할 수 없음
        // 예외 case -> n = 4, s = 1, seq = [1, -1, 1, 2]
    }

    for (int i = index; i < n; ++i) {
        if (!visited[i]) { // 만약 수열의 i번째 숫자가 포함되지 않은 상태라면,
            visited[i] = true;
            dfs(sum + seq[i], s_cnt + 1, i + 1);
            visited[i] = false;
        }
    }
}

int main() {
    cin >> n >> s;
    for (int i = 0; i < n; ++i) {
        cin >> seq[i];
    }

    dfs(0, 0, 0);

    cout << cnt << '\n';

    return 0;
}