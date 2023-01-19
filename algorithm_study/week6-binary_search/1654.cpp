#include <iostream>
#include <vector>

using namespace std;

const int MAX = 2147483647; // int 범위 최댓값

// * n개 이상의 랜선을 만들 수 있는 최대 랜선 길이
// 다른 문제랑 섞여있을 때 그리디 알고리즘으로 접근할 생각이 들 수도 있을 것 같다.
// -> 근데 그리디 문제라기엔 타당한 전제를 설정하기가 어려움
// -> 브루트포스로 해결할 수 밖에 없을 것 같은데, 브루트포스는 시간초과가 뜰 것으로 예상됨.
// -> 이분탐색으로 해결하자 
// ? 이분 탐색 :: 전수 비교(= 브루트포스)를 해야하지만 시간초과가 나는 경우에 사용하는 느낌..?

int main() {
    int k, n; // k: 랜선의 수, n: 필요한 랜선 수

    cin >> k >> n;

    unsigned int start = 1, end = 0, mid;
    vector<int> lan(k);
    for (int i = 0; i < k; ++i) {
        cin >> lan[i];
        if (lan[i] > end) { // 주어진 랜선 중 가장 작은 길이를 end로 설정
            end = lan[i];
        }
    }

    long long sum; 
    unsigned int result;
    while (start <= end) {
        sum = 0;
        mid = (start + end) / 2;
        for (int i = 0; i < k; ++i) {
            sum += lan[i] / mid;
        }

        if (sum >= n) {
            result = mid;
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }

    cout << result << '\n';

    return 0;
}

// 802
// 743
// 457
// 539

// 가능한 최대 랜선 길이 == k개의 랜선 중 가장 짧은 랜선 길이 -> X
// 가능한 최대 랜선 길이 == k개의 랜선 중 가장 긴 랜선 길이 -> O
// 1. 1 ~ 457 숫자를 나열 (= 가능한 랜선 길이를 나열)
// 2. 각 반복마다 mid 값을 설정하고, mid값을 랜선 길이로 했을 때 총 몇 개로 쪼갤 수 있는지 계산
// 3-1. 2에서 구한 값이 n개 이상일 경우, max_result 값 갱신
// 3-1. 앞에서 구한 것보다 더 크게 구할 수 있는지 탐색하기 위해 start를 mid + 1로 변경
// 3-2. 2에서 구한 값이 n개 미만일 경우, mid를 더 짧게 해야하기 때문에 end를 mid - 1로 변경

// + 다행히 k의 범위가 10,000 이하이기 때문에, 이분탐색을 할 때마다 총 랜선 수를 구해도 ok
// -> "가능한 최대 랜선 길이"의 최댓값은 약 30(= log2,000,000,000)이고, 여기에 10,000를 곱하면 300,000 -> 시간 충분