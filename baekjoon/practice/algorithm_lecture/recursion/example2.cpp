#include <iostream>

// ? 에어컨
// ? 현재 온도와 희망온도를 받아 리모컨 버튼을 최소한으로 누르는 횟수를 구하시오
// ? 단, 리모컨에는 1, -1, 5, -5 버튼만 존재한다. 단, 버튼은 10번 이상 누를 수 없다. 

using namespace std;

int current, hope, result = 100;

void dfs(int now, int cnt) {
    if (cnt >= 10) {
        return ;
    }

    if (now == hope) {
        if (cnt < result) {
            result = cnt;
        }
    }

    if (now >= hope) {
        return ;
    }

    dfs(now + 1, cnt + 1);
    dfs(now - 1, cnt + 1);
    dfs(now + 5, cnt + 1);
    dfs(now - 5, cnt + 1);
}

int main() {
    cin >> current >> hope;

    dfs(current, 0);

    cout << result << '\n';

    return 0;
}