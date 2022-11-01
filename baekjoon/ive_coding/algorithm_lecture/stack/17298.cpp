#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> input;
    vector<int> result(n, -1);

    stack<int> s; // 오큰수가 없는 수의 인덱스 번호를 저장

    int current;
    for (int i = 0; i < n; ++i) {
        cin >> current;
        input.push_back(current);

        if (s.empty() || input[s.top()] >= current) {
            s.push(i);
        } else {
            result[s.top()] = current;
            s.pop();
            s.push(i);
        }
    }

    while (!s.empty()) {
        current = input[s.top()];
        s.pop();
        while (!s.empty() && input[s.top()] < current) {
            result[s.top()] = current;
            s.pop();
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << result[i] << ' ';
    }

    return 0;
}