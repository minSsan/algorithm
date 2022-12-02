// ? 2293번에서 "사용한 동전의 구성이 같은데, 순서만 다른 것은 같은 경우이다." 조건을 무시한 풀이

#include <iostream>

using namespace std;

int n, k, cnt, coin[101];

void dfs(int now) {
    if (now == k) {
        cnt++;
    }

    if (now >= k) {
        return ;
    }

    for (int i = 0; i < n; ++i) {
        dfs(now + coin[i]);
    }
}

int main() {
    cin >> n >> k;

    int input_num;
    for (int i = 0; i < n; ++i) {
        cin >> input_num;
        coin[i] = input_num;
    }

    dfs(0);

    cout << cnt << '\n';

    return 0;
}