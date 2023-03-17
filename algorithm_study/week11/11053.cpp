#include <iostream>

using namespace std;

// * 자기 자신보다 작은 수의 갯수를 저장하면 되지 않을까?
// * -> 단, 무작정 작은 수의 갯수를 세면 안된다. 수열이 새로 시작되는 부분이 발생할 수 있기 때문 
// ?    ex. 10 15 5 7 9 11 같은 경우, 11보다 작은 수는 4개지만 정답은 4+1이 아님. 5부터 시작하는 수열로 최대값을 얻을 수 있기 때문
// * -> 자신보다 작은 숫자들 중, 그 숫자가 이루는 수열 길이가 가장 큰 것을 찾아야 함.
// ?    ex. 10 -> 0개, 15 -> 1개, 5 -> 0개, 7 -> 1개, 9 -> 2개, 11 -> 3개 (숫자 9까지 최대 길이가 3인 수열을 이룰 수 있기 때문)

int main() {
    int n;
    cin >> n;

    int sequence[n];
    for (int i = 0; i < n; ++i) {
        cin >> sequence[i];
    }

    int lower[n]; // Ai 보다 앞에 있는 값들 중, Ai 보다 작은 수의 갯수
    lower[0] = 0; // A0 보다 앞에 있는 값 없음.

    int result = 0;
    for (int i = 1; i < n; ++i) { // ? 6
        int lower_max = 0; // 자기 자신보다 작은 수의 갯수

        // 자신보다 앞에 있는 값들을 모두 탐색
        for (int j = 0; j < i; ++j) {
            // 자신보다 작은 숫자가 나오면, 
            if (sequence[i] > sequence[j]) {
                // 해당 숫자가 갖는 lower값을 검사
                if (lower[j] + 1 > lower_max) {
                    lower_max = lower[j] + 1;
                }
            }
        }
        lower[i] = lower_max;
        if (lower[i] > result) {
            result = lower[i]; // ? 2
        }
    }

    cout << result + 1 << '\n';

    return 0;
}