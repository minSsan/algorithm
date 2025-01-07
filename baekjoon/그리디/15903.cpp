#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    priority_queue<long long, vector<long long>, greater<long long>> pq;

    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        pq.push(num);
    }

    while (m--) {
        long long a = pq.top(); pq.pop();
        long long b = pq.top(); pq.pop();

        pq.push(a+b);
        pq.push(a+b);
    }

    long long sum = 0;
    while (!pq.empty()) {
        sum += pq.top();
        pq.pop();
    }

    cout << sum << '\n';

    return 0;
}