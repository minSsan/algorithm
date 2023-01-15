#include <iostream>
#include <vector>

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

    vector<int> dp(cnt.size(), 0);
    
    // * 1. 맨 처음 등장한 방향이 채택되는 경우의 최대 갯수 구하기
    int result; // 누적 최대 합, 결과 값
    dp[0] = cnt[0];
    int tmp = 0; // 아직 반영하지 않은 누적 합
    // ! [3, -3, 1, -1, 1, -2]
    for (int i = 1; i < cnt.size(); ++i) {
        if (i % 2 == 0) {
            int current = dp[i-1] + tmp + cnt[i];
            if (current >= dp[i-1] && cnt[i] >= dp[i-1]) {
                if (current >= cnt[i]) {
                    dp[i] = current;
                } else {
                    dp[i] = cnt[i];
                }
                tmp = 0;
            } else if (cnt[i] >= dp[i-1]) {
                dp[i] = cnt[i];
                tmp = 0;
            } else if (current >= dp[i-1]) {
                dp[i] = current;
                tmp = 0;
            } else {
                dp[i] = dp[i-1];
                tmp += cnt[i];
            }
        } else {
            dp[i] = dp[i-1];
            tmp += cnt[i];
        }
    }

    result = dp[dp.size() - 1];
    // result = max_sum;
    
    // * 2. 두 번째로 등장한 방향이 채택되는 경우의 최대 갯수 구하기
    for (int i = 0; i < cnt.size(); ++i) {
        cnt[i] = -1 * cnt[i];
        dp[i] = 0;
    }

    dp[0] = cnt[0];
    tmp = 0;
    // ! [-3, 3, -1, 1, -1, 2]
    // ! [-2, 4]
    for (int i = 1; i < cnt.size(); ++i) {
        if (i % 2 == 1) {
            int current = dp[i-1] + tmp + cnt[i];
            if (current >= dp[i-1] && cnt[i] >= dp[i-1]) {
                if (current >= cnt[i]) {
                    dp[i] = current;
                } else {
                    dp[i] = cnt[i];
                }
                tmp = 0;
            } else if (cnt[i] >= dp[i-1]) {
                dp[i] = cnt[i];
                tmp = 0;
            } else if (current >= dp[i-1]) {
                dp[i] = current;
                tmp = 0;
            } else {
                dp[i] = dp[i-1];
                tmp += cnt[i];
            }
        } else {
            dp[i] = dp[i-1];
            tmp += cnt[i];
        }
    }

    // cout << "max_sum: " << max_sum << '\n';

    // cout << dp[dp.size() - 1] << '\n';

    result = max(result, dp[dp.size() - 1]);
    // result = max(result, max_sum);

    cout << result << '\n';

    return 0;
}

// * 값이 최대가 나오는 시작점과 끝점을 결정해야 한다.

// 1 1 2 1 2 :: 2
// [2, -1, 1, -1], max = 
// 1 2 1 2 1 // 자기 자신을 범위 내에 포함하냐 안하느냐
// 1 1 -1 1 -1 :: 

// 1 1 2 2 2 2
// 1 2 1 2 3 4
// cnt_1 = 2, cnt_2 = 4
// [2, -4]
// 1 1 -1 -1 -1 -1

// 1 1 1 1 2 2 2 1 1 1 1 :: 5
// 1 2 3 4 1 2 3 1 2 3 4
// cnt_1 = 4, cnt_2 = 3, cnt_1 = 8
// [4, -3, 4]
