#include <iostream>
#include <queue>

using namespace std;

int main() {
    pair<int, int> a;
    cin >> a.first >> a.second;

    cout << a.first << ' ' << a.second << '\n';

    pair<int, int> b;
    cin >> b.first >> b.second;

    if (a > b) {
        cout << "a\n";
    } else {
        cout << "b\n";
    }

    // ---------------
    priority_queue<pair<int, int>> pq;
    pq.push({1, 2});

    pair<int, int> ans = pq.top();

    cout << ans.first << ans.second << '\n';

    return 0;
}
