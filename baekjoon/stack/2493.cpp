#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// 6 9 5 7 4
// 4 5 6 7 3

int main() {
    int n;
    cin >> n;

    vector<int> input;
    vector<int> result(n, 0);

    stack<int> s;

    int current;
    // 6 9 5 7 4
    // input
    // 6 9 5 7 4
    // s
    // 1 3
    // result
    // 0 0 2 2 4
    for (int i = 0; i < n; ++i) {
        cin >> current;
        input.push_back(current);
        
        while (!s.empty() && input[s.top()] < current) {
            s.pop();
        }

        if (!s.empty() && input[s.top()] > current) {
            result[i] = s.top() + 1;
        }

        s.push(i);
    }

    for (int i = 0; i < n; ++i) {
        cout << result[i] << ' ';
    }

    return 0;
}