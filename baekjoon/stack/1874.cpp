#include <iostream>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);

    int n, N;
    cin >> n;
    N = n;
    
    stack<int> seq_stack;
    int sequence[100001] = {0};

    while (n--) {
        cin >> sequence[n];
    }

    int arrow_idx = 0;
    int complete_count = 0;
    string result = "";

    for (int i = 1; i <= N; ++i) {
        if (i != sequence[arrow_idx]) {
            if (i < sequence[arrow_idx]) {
                seq_stack.push(i);
                result += "+\n";
            }
            else {
                result = "NO\n";
                cout << result;
                return 0;
            }
        }
        else {
            while (seq_stack.size() != complete_count) {
                seq_stack.pop();
                result += "-\n";
            }
            seq_stack.push(i);
            result += "+\n";
            arrow_idx++;
            complete_count++;
        }
    }
    
    while (!seq_stack.empty()) {
        seq_stack.pop();
        result += "-\n";
    }

    cout << result;

    return 0;
}