#include <iostream>
#include <vector>

using namespace std;

// * z(승률) = (y * 100) / x
// * 앞으로의 모든 게임은 무조건 이긴다.
// ? 지금까지 진 횟수만큼 모두 이기면 ? -> 무조건 승률 올라감
// ? 지금까지 진 횟수만큼을 이진탐색 -> z + 1인 값이 처음 나오는 위치 구하기
// ex. 10 8 -> [1, 2], z + 1 = 81
// ex. 100 80 -> [1, 2, 3, 4, 5, 6, 7, ..., 20], z + 1 = 81
// start = 0, end = 19, mid = 9
// 1. mid 값으로 구한 승률 == 81 :: 찾는 값보다 크거나 같기 때문에 왼쪽에서 다시 탐색
// -> start = 0, end = mid - 1 = 8, mid = 4 :: [1, 2, 3, ..., 9]
// 2. mid 값으로 구한 승률 == 80 :: 찾는 값보다 작기 때문에 오른쪽에서 다시 탐색
// -> start = md + 1 = 5, end = 8, mid = 6 :: [6, 7, 8, 9]
// 3. mid 값으로 구한 승률 = 81 :: 찾는 값보다 크거나 같기 때문에 왼쪽에서 다시 탐색
// -> start = 5, end = mid - 1 = 5, mid = 0 :: [6]
// 4. mid 값으로 구한 승률 = 81 :: 찾는 값보다 크거나 같기 때문에 왼쪽에서 다시 탐색
// -> start = 5, end = mid - 1 = 4 종료

int main() {
    int x; long long y; // x: 게임 진행 수, y: 이긴 횟수
    cin >> x >> y;

    int z;
    long long tmp = y * 100;
    // cout << "tmp: " << tmp << '\n'; 
    z = tmp / x;

    // cout << "z: " << z << '\n';

    int start = 1, end = x;
    int mid;
    int min_cnt = 1000000000; // 조건을 만족하는 현재까지의 최소 이긴 횟수
    int min_odds = 100; // 조건을 만족하는 현재까지의 최소 승률 값
    int current_odds;

    tmp = (y + end) * 100;
    if (tmp / (x + end) == z) { // 아무리 이겨도 승률을 올릴 수 없다면
        cout << -1 << '\n'; // -1 출력 후 종료
        return 0;
    }

    while (start <= end) {
        mid = (start + end) / 2;
        tmp = (y + mid) * 100;
        current_odds = tmp / (x + mid);
        // cout << "mid: " << mid << '\n';
        // cout << "current_odds: " << current_odds << '\n';
        // cout << "min_odds: " << min_odds << '\n';
        
        if (current_odds > z) { // z보다 큰 승률이 나왔을 때
            min_cnt = mid;
            end = mid - 1;
        } else { // z랑 동일한 승률이 나왔을 때 -> 별도의 작업 필요 없이 재탐색
            start = mid + 1;
        }
    }

    cout << min_cnt << '\n';

    return 0;
}