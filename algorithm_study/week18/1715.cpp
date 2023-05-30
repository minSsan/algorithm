#include <iostream>
#include <queue>

using namespace std;

int main() {
    int n;
    cin >> n;
    priority_queue<int, vector<int>, greater<int>> pq;
    int input_num;
    for (int i = 0; i < n; ++i) {
        cin >> input_num;
        pq.push(input_num);
    }

    int a, b, result = 0;
    while (pq.size() > 1) {
        a = pq.top(); pq.pop();
        b = pq.top(); pq.pop();
        result += (a + b);
        pq.push(a+b);
    }

    cout << result << '\n';

    return 0;
}