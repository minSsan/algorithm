// ? 재귀 - 백트래킹(재귀의 시간초과 문제 개선을 위해 나온 알고리즘)
// ! 재귀 문제는 설계를 먼저 해야한다.

// ex) 계단 오르기 문제. n칸의 계단을 1칸 혹은 2칸씩 오르는 경우의 수 구하기

#include <iostream>

using namespace std;

int n, cnt;

void dfs(int now) {
    // ? n칸을 모두 올라왔을 때
    if (now == n) {
        cnt++;
        return ;
    }

    // ? n칸을 넘겼을 때 멈추기
    if (now > n) {
        return ;
    }

    dfs(now + 1);
    dfs(now + 2);
}

int main() {
    cin >> n;

    dfs(0);

    cout << cnt << '\n';

    return 0;
}