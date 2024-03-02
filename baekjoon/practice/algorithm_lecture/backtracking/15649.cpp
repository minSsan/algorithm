#include <iostream>
#include <vector>

using namespace std;

// * 문제: 1부터 N까지 자연수 중에서, 중복 없이 M개를 고른 수열

// - 첫 번째 자리에 등장하는 숫자를 기준으로 경우 나누기?
// - 각 가지에서 다음 가지로 넘어갈 때, 방문처리 되지 않은 숫자를 모두 탐색하기

int n, m;
// ? 1 ~ n까지의 숫자가 각각 수열에서 등장했는지 저장하는 배열
bool isExist[9]; // 가능한 n의 범위 최대값은 8
vector<int> result;

void backtracking() {
    // 하나의 수열이 완성되었다면,
    if (result.size() == m) {
        // 해당 수열을 출력한 후, 함수를 종료시킨다. 
        for (int i = 0; i < result.size(); ++i) {
            cout << result[i] << ' ';
        }
        cout << '\n';
        return ;
    }

    for (int i = 1; i <= n; ++i) {
        if (!isExist[i]) {
            // 수열의 맨 뒷자리에 추가하고, 그 다음에 올 숫자들을 탐색한다.
            isExist[i] = true;
            result.push_back(i);

            backtracking();

            // 하나의 수열이 출력되면, 수열의 마지막 번째 요소를 제거한다.
            isExist[i] = false;
            result.pop_back();
        }
    }
}

// ? [t, t, f, f]
// ? [1, 2]

int main() {
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        if (!isExist[i]) {
            result.push_back(i);
            isExist[i] = true;

            backtracking();

            result.pop_back();
            isExist[i] = false;
        }
    }

    return 0;
}