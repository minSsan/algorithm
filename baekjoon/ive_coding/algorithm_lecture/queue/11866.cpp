#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, k;
    queue<int> q;
    vector<int> result;

    cin >> n >> k;

    for (int i = 1; i <= n; ++i) {
        q.push(i);
    }

    while (!q.empty()) {
        for (int i = 0; i < k-1; ++i) {
            q.push(q.front());
            q.pop();
        }
        result.push_back(q.front());
        q.pop();
    }

    cout << '<';

    for (int i = 0; i < n - 1; ++i) {
        cout << result[i] << ", ";
    }

    cout << result[n-1] << ">\n";

    return 0;
}