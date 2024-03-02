#include <iostream>

// ? 에어컨
// ? 현재 온도와 희망온도를 받아 리모컨 버튼을 최소한으로 누르는 횟수를 구하시오.
// ? 단, 리모컨에는 1, 3, 5, 10 버튼만 존재한다.

using namespace std;

int current, hope, cnt, minimum = 100;

void dfs(int temp) {
    if (temp == hope) {
        if (minimum > cnt) {
            minimum = cnt;
        }
    }

    if (temp >= hope) {
        cnt--; // ? 가지 하나를 종료할 때 cnt 값을 감소시키게 되면, 동일 선상(세로)에 존재하는 다음 가지에서 cnt가 1 감소한채로 실행된다.
        return ;
    }
    
    cnt++;
    dfs(temp + 1);
    dfs(temp + 3);
    dfs(temp + 5);
    dfs(temp + 10);
}

int main() {
    cin >> current >> hope;

    dfs(current);

    cout << minimum << '\n';

    return 0;
}