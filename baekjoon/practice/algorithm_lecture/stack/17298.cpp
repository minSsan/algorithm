#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> input(n);
    vector<int> result(n, -1);

    stack<int> s; // 오큰수가 없는 수의 인덱스 번호를 저장

    int current;
    for (int i = 0; i < n; ++i) {
        cin >> current;
        input[i] = current;

        
        while (!s.empty() && input[s.top()] < input[i]) {
            result[s.top()] = input[i];
            s.pop();
        }
        
        s.push(i);
    }

    for (int i = 0; i < n; ++i) {
        cout << result[i] << ' ';
    }

    return 0;
}