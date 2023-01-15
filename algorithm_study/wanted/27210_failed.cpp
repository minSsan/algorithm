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

    // * test code ---------
    // for (int i = 0; i < cnt.size(); ++i) {
    //     cout << cnt[i] << ' ';
    // }
    // cout << '\n';
    // * -------------------
    
    // * 1. 맨 처음 등장한 방향이 채택되는 경우의 최대 갯수 구하기
    int result; // 누적 최대 합, 결과 값
    
    // ? 현재에는 누적 합이 max_sum보다 작을지 몰라도, 나중에 합이 더해지면서 max_sum보다 커질 수도 있다 (ex. 5 -4 3 -3 7) -> tmp에 저장해두기 
    int tmp = 0; // max_sum에 아직 반영되지 않은 값의 총합
    
    int max_sum = 0, current_sum; // 현재까지의 최대 합, 이전 값 + 현재 값까지 반영한 누적 합(= 최대 합과 비교해야 할 값)
    for (int i = 0; i < cnt.size(); ++i) {
        if (i % 2 == 0) {
            current_sum = max_sum + tmp + cnt[i];
            // * 1. 현재 값까지의 누적 합이 최대 누적 합보다 큰 경우 -> 누적 합 갱신, tmp 초기화
            // * 2. 현재 값 자체가 최대 누적 합보다 큰 경우 -> 누적 합을 현재 값으로 초기화 (현재 값부터 다시), tmp 초기화
            // * 3. 현재 값도 최대 누적보다 작고, 현재 값까지의 누적 합도 최대 누적보다 작은 경우 -> 누적 합 유지, tmp 갱신
            if (current_sum >= max_sum) {
                max_sum = max(current_sum, cnt[i]); // 현재 값(= cnt[i])이 더 클 수 있으므로 max 함수 사용
                tmp = 0;
            } else if (cnt[i] >= max_sum) {
                max_sum = cnt[i]; // current_sum < max_sum 을 이미 만족하기 때문에 max 사용 x
                tmp = 0;
            } else {
                tmp += cnt[i];
            }
        } else {
            tmp += cnt[i];
        }
    }

    result = max_sum;

    // * test code ------------
    // cout << "result: " << result << '\n';
    // * ----------------------
    
    for (int i = 0; i < cnt.size(); ++i) {
        cnt[i] = -1 * cnt[i];
    }
    // * 2. 두 번째로 등장한 방향이 채택되는 경우의 최대 갯수 구하기
    max_sum = 0;
    tmp = 0;
    for (int i = 0; i < cnt.size(); ++i) {
        if (i % 2 == 1) {
            current_sum = max_sum + tmp + cnt[i];
            // * 1. 현재 값까지의 누적 합이 최대 누적 합보다 큰 경우 -> 누적 합 갱신, tmp 초기화
            // * 2. 현재 값 자체가 최대 누적 합보다 큰 경우 -> 누적 합을 현재 값으로 초기화 (현재 값부터 다시), tmp 초기화
            // * 3. 현재 값도 최대 누적보다 작고, 현재 값까지의 누적 합도 최대 누적보다 작은 경우 -> 누적 합 유지, tmp 갱신
            if (current_sum >= max_sum) {
                max_sum = max(current_sum, cnt[i]);
                tmp = 0;
            } else if (cnt[i] >= max_sum) {
                max_sum = cnt[i];
                tmp = 0;
            } else {
                tmp += cnt[i];
            }
        } else {
            tmp += cnt[i];
        }
    }

    result = max(result, max_sum);

    cout << result << '\n';

    return 0;
}
