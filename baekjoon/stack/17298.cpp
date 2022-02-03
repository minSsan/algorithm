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
    stack<int> nge_idx;
    vector<int> result(N);
    
    for (int i = 0; i < N; ++i) {
        cin >> input_num[i];
    }

    result[N-1] = -1;
    for (int i = 0; i < N; ++i) {
        while (!nge_idx.empty() && input_num[nge_idx.top()] < input_num[i]) {
            result[nge_idx.top()] = input_num[i];
            nge_idx.pop();
        }
        nge_idx.push(i);
    }

    while (!nge_idx.empty()) {
        result[nge_idx.top()] = -1;
        nge_idx.pop();
    }

    for (int i = 0; i < N; ++i) {
        cout << result[i] << ' ';
    }

    return 0;
}