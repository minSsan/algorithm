#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, max, current;
    cin >> N;
    vector<int> input_num(N);
    stack<int> result;

    for (int i = 0; i < N; ++i) {
        cin >> input_num[i];
    }

    max = 0;
    result.push(-1);
    for (int i = N-1; i > 0; --i) {
        if (input_num[i] > max) {
            max = input_num[i];
        }
        current = input_num[i-1];

        if (input_num[i] > current) {
            result.push(input_num[i]);
        }
        else {
            if (max > current) {
                result.push(max);
            }
            else {
                result.push(-1);
            }
        }
    }

    while (!result.empty()) {
        cout << result.top() << ' ';
        result.pop();
    }

    return 0;
}