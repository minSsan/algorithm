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
        return ;
    }

    cnt++;
    
    dfs(temp + 1);
    dfs(temp + 3);
    dfs(temp + 5);
    dfs(temp + 10);
    
    cnt--;
}

void dfs2(int temp, int min_cnt) {
    if (temp == hope) {
        if (minimum > min_cnt) {
            minimum = min_cnt;
        }
    }

    if (temp >= hope) {
        return ;
    }
    
    dfs2(temp + 1, min_cnt + 1);
    dfs2(temp + 3, min_cnt + 1);
    dfs2(temp + 5, min_cnt + 1);
    dfs2(temp + 10, min_cnt + 1);
}

int main() {
    cin >> current >> hope;

    // dfs(current);
    dfs2(current, 0);

    cout << minimum << '\n';

    return 0;
}