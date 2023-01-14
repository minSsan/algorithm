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
    int max_sum = 0, result; // 누적 최대 합, 결과 값
    dp[0] = cnt[0];
    max_sum = cnt[0];
    for (int i = 1; i < cnt.size(); ++i) {
        if (i % 2 == 0) {
            max_sum = max(dp[i-1] + cnt[i], max_sum); // ? 현재까지의 최대 값과, 현재 값을 더한 값 중 더 큰 값을 저장
            if (max_sum + cnt[i] > max_sum) {
                if (cnt[i] > max_sum + cnt[i]) {
                    max_sum = cnt[i];
                } else {
                    max_sum += cnt[i];
                }
            }
        } else {
            dp[i] = dp[i-1] + cnt[i];
        }
        
        // sum = dp[i-1] + cnt[i]; // ? 현재 범위를 포함한 값
        // if (i % 2 == 0) { // ? 2칸씩 확인 (바로 인접한 것은 역방향이므로, 역방향만 더하는 것은 최댓값을 구하는데에 의미가 없음 -> 역방향을 더하면 그 다음 정방향까지 더한 뒤에 최댓값인지 확인해야 함)
        //     if (dp[i-1] > sum || cnt[i] > sum) { // ? 현재 범위를 포함한 것보다, 포함하지 않는 것이 이득인 경우
        //         dp[i] = max(dp[i-1], cnt[i]); // ? 이전 기록을 쓰는 것 vs 현재 범위부터 다시 시작하는 것
        //     } 
        //     else if (sum > dp[i-1]) {
        //         dp[i] = sum;
        //     }
        //     else {
        //         dp[i] = dp[i-1];
        //     }
        //     // dp[i] = sum;
        // } else {
        //     dp[i] = dp[i - 1];
        // }
    }

    result = dp[dp.size() - 1];

    std::cout << result << '\n';
    
    // * 2. 두 번째로 등장한 방향이 채택되는 경우의 최대 갯수 구하기
    sum = 0;
    for (int i = 0; i < cnt.size(); ++i) {
        cnt[i] = -1 * cnt[i];
        dp[i] = 0;
    }

    dp[0] = cnt[0];
    for (int i = 1; i < cnt.size(); ++i) {
        sum += cnt[i]; // ? 현재 범위를 포함한 값
        if (i % 2 == 1) { // ? 2칸씩 확인 (바로 인접한 것은 역방향이므로, 역방향만 더하는 것은 최댓값을 구하는데에 의미가 없음 -> 역방향을 더하면 그 다음 정방향까지 더한 뒤에 최댓값인지 확인해야 함)
            if (dp[i-1] > sum || cnt[i] > sum) { // ? 현재 범위를 포함한 것보다, 포함하지 않는 것이 이득인 경우
                dp[i] = max(dp[i-1], cnt[i]); // ? 이전 기록을 쓰는 것 vs 현재 범위부터 다시 시작하는 것
            } 
            else if (sum > dp[i-1]) {
                dp[i] = sum;
            }
            else {
                dp[i] = dp[i-1];
            }
            // dp[i] = sum;
        } else {
            dp[i] = dp[i - 1];
        }
        // if (i % 2 == 1) { // ? 2칸씩 확인 (바로 인접한 것은 역방향이므로, 역방향만 더하는 것은 최댓값을 구하는데에 의미가 없음 -> 역방향을 더하면 그 다음 정방향까지 더한 뒤에 최댓값인지 확인해야 함)
        //     if (sum + cnt[i] > dp[i-1]) {
        //         sum += cnt[i];
        //     }

        //     if (cnt[i] > sum && cnt[i] > dp[i-1]) {
        //         dp[i] = cnt[i];
        //         sum = cnt[i];
        //     } else if (sum > dp[i-1]) {
        //         dp[i] = sum;
        //     } else {
        //         dp[i] = dp[i-1];
        //     }
        // } else {
        //     dp[i] = dp[i - 1];
        // }
    }

    result = max(result, dp[dp.size() - 1]);

    std::cout << result << '\n';

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
