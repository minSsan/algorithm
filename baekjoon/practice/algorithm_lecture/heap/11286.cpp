#include <iostream>
#include <queue>

using namespace std;

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    // priority_queue<pair<int, int>> pq;
    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    int x;
    while (n--) {
        cin >> x;
        if (x == 0) {
            if (pq.empty()) {
                cout << '0';
            } else {
                cout << pq.top().second;
                pq.pop();
            }
            cout << '\n';
        } else {
            if (x > 0) {
                pq.push({x, x});
            } else {
                pq.push({-x, x});
            }
        }
    }

    return 0;
}