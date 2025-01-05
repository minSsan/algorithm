#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 전제: 앞에 있는 회의가 일찍 끝마칠수록, 더 많은 회의를 진행할 수 있다.
// -> 회의가 몇 시에 시작해서 몇 시간 동안 진행하는지와 관계 없이, 회의가 끝나는 시간만 고려한다.

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> v; // {end, start}
    for (int i = 0; i < n; ++i) {
        int start, end;
        cin >> start >> end;
        v.push_back({end, start});
    }

    sort(v.begin(), v.end());

    int last = 0, cnt = 0;
    for (pair<int, int> i : v) {
        int start = i.second, end = i.first;
        if (start >= last) {
            ++cnt;
            last = end;
        }
    }

    cout << cnt << '\n';
    return 0;
}