#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    // 최소 힙
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    pair<int, string> input;

    while (n--) {
        cin >> input.first >> input.second;
        pq.push(input);
    }

    while (!pq.empty()) {
        cout << pq.top().first << ' ' << pq.top().second << '\n';
        pq.pop();
    }

    return 0;
}