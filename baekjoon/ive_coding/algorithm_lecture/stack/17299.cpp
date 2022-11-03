#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> count(1000001, 0);
    vector<int> result(n, -1);
    vector<int> input;

    stack<int> s; // 오등큰수가 없는 수

    int current;
    for (int i = 0; i < n; ++i) {
        cin >> current;
        count[current]++;
        input.push_back(current);
    }
    
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