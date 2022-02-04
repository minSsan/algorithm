#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> input_num(N);
    vector<int> count(1000002, 0);
    vector<int> result(N);
    stack<int> input_idx;
    int num;

    for (int i = 0; i < N; ++i) {
        cin >> num;
        input_num[i] = num;
        count[num]++;
    }

    for (int i = 0; i < N; ++i) {
        while (!input_idx.empty() && count[input_num[input_idx.top()]] < count[input_num[i]]) {
            result[input_idx.top()] = input_num[i];
            input_idx.pop();
        }
        input_idx.push(i);
    }

    while (!input_idx.empty()) {
        result[input_idx.top()] = -1;
        input_idx.pop();
    }

    for (int i = 0; i < N; ++i) {
        cout << result[i] << ' ';
    }
    
    return 0;
}