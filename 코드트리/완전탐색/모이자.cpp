#include <iostream>
#include <vector>
#include <climits>

using namespace std;

//? n개의 집 중 한 곳에 전부 모이려고 한다.
//? 모든 사람들의 이동거리 합이 최소가 되도록 한다.
int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    int distance;
    int min_sum = INT_MAX;
    // i번째 집으로 모두 모이는 경우
    for (int i = 0; i < n; ++i) {
        int sum = 0;
        // j번째 집에 있는 사람들의 이동거리
        for (int j = 0; j < n; ++j) {
            distance = abs(i-j);
            sum += distance * v[j]; // j번째 집에 있는 사람 수 * 거리
        }

        if (sum < min_sum) min_sum = sum;
    }

    cout << min_sum << '\n';

    return 0;
}