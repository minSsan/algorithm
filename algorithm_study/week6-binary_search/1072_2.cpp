#include <iostream>
#include <vector>

using namespace std;

// * z(승률) = (y * 100) / x
// * 앞으로의 모든 게임은 무조건 이긴다.
// ? 지금까지 진 횟수만큼을 이진탐색 -> z + a인 값이 처음 나오는 위치 구하기

int main() {
    int x; long long y; // x: 게임 진행 수, y: 이긴 횟수
    cin >> x >> y;

    int z;
    long long tmp = y * 100;
    z = tmp / x;

    int start = 1, end = x;
    int mid;
    int min_cnt = 1000000000; // 조건을 만족하는 현재까지의 최소 이긴 횟수
    long long min_odds = 100; // 조건을 만족하는 현재까지의 최소 승률 값
    long long current_odds;

		tmp = (y + end) * 100;
    if (tmp / (x + end) == z) { // 아무리 이겨도 승률을 올릴 수 없다면
        cout << -1 << '\n'; // -1 출력 후 종료
        return 0;
    }

    while (start <= end) {
        mid = (start + end) / 2;
        tmp = (y + mid) * 100;
        current_odds = tmp / (x + mid);
        
        if (current_odds > z) { // z보다 큰 승률이 나왔을 때
            if (current_odds <= min_odds) { // 현재까지의 최소 승률보다 작거나 같을 때
                min_odds = current_odds; // 최소 승률을 갱신
                if (mid < min_cnt) { // 현재 이긴 횟수가 최소 이긴 횟수보다 작을 때
                    min_cnt = mid;
                }
            }
            end = mid - 1;
        } else { // z랑 동일한 승률이 나왔을 때 -> 별도의 작업 필요 없이 재탐색
            start = mid + 1;
        }
    }

    cout << min_cnt << '\n';

    return 0;
}