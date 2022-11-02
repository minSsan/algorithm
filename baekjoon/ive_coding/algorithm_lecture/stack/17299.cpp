#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> count(n+1, 0);
    vector<int> result(n, -1);
    vector<int> input;

    stack<int> s; // 오등큰수가 없는 수

    int current;
    for (int i = 0; i < n; ++i) {
        cin >> current;
        count[current]++;
        input.push_back(current);
    }
    // s: 0 1 6
    // result
    // 0 1 2 3 4 5 6 7 
    // -1 -1 1 2 2 1 -1 -1
    for (int i = 0; i < n; ++i) {
        current = input[i];

        while (!s.empty() && count[input[s.top()]] < count[current]) {
            result[s.top()] = current;
            s.pop();
        }

        s.push(i);
    }

    for (int i = 0; i < n; ++i) {
        cout << result[i] << ' ';
    }

    return 0;
}