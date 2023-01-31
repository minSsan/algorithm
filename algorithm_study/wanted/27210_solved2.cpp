#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> directions(n);

    for (int i = 0; i < n; ++i) {
        cin >> directions[i];
    }

    // * 같은 방향끼리 묶기 -> 단, 처음 등장한 방향을 기준으로 양수/음수 결정 (= 무조건 처음 등장한 방향을 양수로 저장)
    // ex. 1 1 2 2 1 -> [2, -2, 1]
    // ex. 2 2 1 1 2 -> [2, -2, 1]
    vector<int> cnt;
    int sequence = 1; // 연속해서 나온 횟수

    for (int i = 1; i < n; ++i) {
        // ? 이전 방향과 동일한 방향이라면
        if (directions[i] == directions[i-1]) {
            // ? 연속 횟수 증가하되, 방향 고려해서 증가
            if (sequence > 0) {
                sequence += 1;
            } else {
                sequence -= 1;
            }
        } else { // ? 이전 방향과 다른 방향이라면
            cnt.push_back(sequence); // ? 지금까지 연속된 횟수를 cnt에 푸시
            // ? 방향 바꾸기
            if (sequence > 0) { // 이전에 양수 방향이였다면,
                sequence = -1; // 다음에는 반대 방향인 음수 방향으로 설정
            } else { // 이전에 음수 방향이였다면
                sequence = 1; // 다음에는 반대 방향인 양수 방향으로 설정
            }
        }
    }

    cnt.push_back(sequence); // 마지막 남은 연속 횟수까지 푸시

    // 5 -7 4 -2 6 - max_sum은 따로 저장해두기
    // 1. max_sum >= total_sum : total_sum과 cnt[i] 중 더 큰 값으로 tmp 갱신
    // 2. max_sum < total_sum : tmp = 0, max_sum = max(total_sum, cnt[i])으로 갱신
    // 2 -1 1 -1

    // * test code ---------
    // for (int i = 0; i < cnt.size(); ++i) {
    //     cout << cnt[i] << ' ';
    // }
    // cout << '\n';
    // * -------------------

    int max_sum = cnt[0]; // 5
    int tmp = max_sum; // 2

    for (int i = 1; i < cnt.size(); ++i) {
        if (i % 2 == 0) {
            int total_sum = tmp + cnt[i];
            if (max_sum >= total_sum) {
                tmp = max(total_sum, cnt[i]); 
            } else {
                max_sum = max(total_sum, cnt[i]);
                tmp = max_sum;
            }
        } else {
            tmp += cnt[i];
        }
    }

    int result = max_sum;

    for (int i = 0; i < cnt.size(); ++i) {
        cnt[i] = -1 * cnt[i];
    }

    max_sum = cnt[1];
    tmp = max_sum;
    for (int i = 2; i < cnt.size(); ++i) {
        if (i % 2 == 1) {
            int total_sum = tmp + cnt[i];
            if (max_sum >= total_sum) {
                tmp = max(total_sum, cnt[i]); 
            } else {
                max_sum = max(total_sum, cnt[i]);
                tmp = max_sum;
            }
        } else {
            tmp += cnt[i];
        }
    }

    result = max(result, max_sum);

    cout << result << '\n';

    return 0;
}

// 3 -5 2 -7