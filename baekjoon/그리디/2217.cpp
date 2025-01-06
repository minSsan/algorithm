#include <iostream>
#include <algorithm>

using namespace std;

// 모든 로프를 사용할 필요는 없음 -> 중량이 적은 것부터 빼서 최대 중량을 비교한다.
// :: 로프가 버틸 수 있는 무게는 최소 중량을 담당하는 로프에 종속되기 때문

int main() {
    int n;
    cin >> n;

    int roap[n];
    for (int i = 0; i < n; ++i) {
        cin >> roap[i];
    }

    int max_w = 0;
    sort(roap, roap + n);

    int cnt = n;
    for (int i = 0; i < n; ++i) {
        int coord_w = roap[i] * cnt;
        if (coord_w > max_w) {
            max_w = coord_w;
        }
        cnt--;
    }

    cout << max_w << '\n';

    return 0;
}