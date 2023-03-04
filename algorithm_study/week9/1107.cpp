#include <iostream>

using namespace std;

const int MAX = 500000 + (500000 - 100); // 999900

bool available[10];

bool check(int num) { // 입력된 숫자의 각 자릿수가 모두 리모컨으로 입력 가능한 숫자인지 확인
    // 0이 입력된 경우 예외 처리
    if (num == 0) {
        return available[0];
    }

    while (num != 0) {
        if (!available[num % 10]) {
            return false;
        }
        num = num / 10;
    }
    return true;
}

int main() {
    for (int i = 0; i < 10; ++i) {
        available[i] = true;
    }

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int num;
        cin >> num;
        available[num] = false;
    }

    int min = abs(n - 100); // 100번 채널부터 +/- 버튼으로 이동

    for (int i = 0; i <= MAX; ++i) {
        if (check(i) && to_string(i).length() + abs(n - i) < min) {
            min = to_string(i).length() + abs(n - i);
        }
    }

    cout << min << '\n';

    return 0;
}