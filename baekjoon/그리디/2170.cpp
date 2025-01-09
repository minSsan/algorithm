#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    pair<int, int> lines[n];
    for (int i = 0; i < n; ++i) {
        cin >> lines[i].first >> lines[i].second;
    }

    sort(lines, lines + n);

    int start = lines[0].first, end = lines[0].second; // 현재 선의 시작점, 끝점
    long long result = 0;

    for (int i = 1; i < n; ++i) {
        if (lines[i].first > end) {
            result += end - start;
            start = lines[i].first;
        }
        end = max(end, lines[i].second);
    }
    result += end - start;

    cout << result << '\n';

    return 0;
}