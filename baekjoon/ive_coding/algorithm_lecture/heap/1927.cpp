#include <iostream>
#include <queue>

using namespace std;

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    priority_queue<int> pq;

    int n;
    cin >> n;

    int x;
    while (n--) {
        cin >> x;
        if (x == 0) {
            if (pq.empty()) {
                cout << '0';
            } else {
                cout << -pq.top();
                pq.pop();
            }
            cout << '\n';
        } else {
            pq.push(-x);
        }
    }

    return 0;
}