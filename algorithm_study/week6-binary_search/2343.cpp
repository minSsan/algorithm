#include <iostream>

using namespace std;

// * n개의 영상을 m개로 나누었을 때, 최대 합이 최소가 되게끔
// ? 블루레이 크기를 바꿔가면서, 블루레이 크기에 맞춰 블루레이의 최소 갯수를 구한다.
// ? 이때, 블루레이의 최소 갯수는 M개이면서 블루레이 크기가 최소인 지점(?)을 찾는다.

int main() {
    int lectures[100000];
    int n, m;
    cin >> n >> m;

    int min_sum = 0; // 초기 min_sum은 모든 강의 시간 중 최대값
    int max_sum = 0; // 초기 max_sum은 모든 강의 시간의 합
    for (int i = 0; i < n; ++i) {
        cin >> lectures[i];
        max_sum += lectures[i];
        if (lectures[i] > min_sum) {
            min_sum = lectures[i];
        }
    }

    int current_sum, lecture_sum, blue_cnt; // current_sum: 현재 각 블루레이의 최대합
    int result = max_sum;
    while (min_sum <= max_sum) {
        current_sum = (min_sum + max_sum) / 2;

        // ? 블루레이의 크기가 current_sum일 때의 블루레이 갯수 (= blue_cnt) 구하기
        // ? 블루레이 크기를 새롭게 설정할 때마다 lecture_sum과 blue_cnt 값은 초기화
        lecture_sum = 0; blue_cnt = 1; // lecture_sum: 현재 블루레이의 강의 시간 합, blue_cnt: 블루레이의 갯수 (M과 비교)
        for (int i = 0; i < n; ++i) {
            if (lecture_sum + lectures[i] <= current_sum) {
                lecture_sum += lectures[i];
            } else { // 합이 최대 블루레이 합보다 커지는 경우
                lecture_sum = lectures[i]; // 그 다음 블루레이 묶음(?)의 크기를 계산하기 위해 초기화
                blue_cnt++; // 블루레이의 갯수 갱신
            }
        }

        // ! blue_cnt가 주어진 m보다 작더라도, current_sum이 result보다 작으면 이를 갱신해줘야 함. 
        // ! -> M개를 모두 채울 필요는 없음(조건에도 안 나와있음). M개보다 작거나 같은 블루레이에 층분히 나눌 수 있으면 ok
        if (blue_cnt <= m && current_sum < result) {
            result = current_sum;
        }

        if (blue_cnt <= m) {
            max_sum = current_sum - 1;
        } else {
            min_sum = current_sum + 1;
        }
    }

    cout << result << '\n';

    return 0;
}