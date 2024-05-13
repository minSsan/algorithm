#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 5000000000

using namespace std;

//* 가장 왼쪽에서 출발하여 오른쪽으로 이동함
//* 힘 = (j - i) * (1 + |A[j| - A[i])
//* 돌을 건널 때 들이는 힘의 최댓값이 가장 작은 경우?

//? 거리가 멀다고 해서 힘이 크다는 보장이 없다.
//? 첫 번째 돌부터 시작해서, 다음에 밟을 돌을 정한다.
//? -> 현재 돌에서 출발할 때, 힘이 가장 적은 경우를 선택한다.(그리디)
//?     -> 항상 최적의 결과를 보장하지 못하므로, 마지막 돌을 선택할 때마다 최솟값을 비교하고 갱신한다.

int main() {
    int n;
    cin >> n;

    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    // i번째 돌까지 이동하는데 필요한 최소 힘
    vector<long long> min_dist(n, MAX);
    int current = 0; // 현재 밟고 있는 돌의 위치
    while (current < n-1)
    {
        int next_coord = n-1; // 다음 current 값 후보
        long long min_k = min_dist[next_coord];
        for (int next = current+1; next < n; ++next) {
            long long k = (next - current) * (1 + abs(v[next] - v[current]));
            min_dist[next] = min(min_dist[next], k);
            if (k < min_k) {
                next_coord = next;
                min_k = k;
            }
        }
        current = next_coord;
    }

    cout << min_dist[n-1] << '\n';

    return 0;
}