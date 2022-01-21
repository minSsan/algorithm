#include <iostream>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string result = "";
    
    stack<int> seq_stack;
    int sequence[100001] = {0};

    for (int i = 0; i < n; ++i) {
        cin >> sequence[i];
    }

    int input_num = 1;
    int arrow_idx = 0;
    
    while (1) {
        // 스택 수열 가능(정상 종료)
        if (seq_stack.empty() && input_num > n) {
            break;
        }
        // 스택 수열 불가능(NO)
        if (!seq_stack.empty() && sequence[arrow_idx] < seq_stack.top()) {
            result = "NO\n";
            break;
        }

        while (input_num <= sequence[arrow_idx]) {
            seq_stack.push(input_num);
            result += "+\n";
            input_num++;
        }
        if (!seq_stack.empty() && seq_stack.top() == sequence[arrow_idx]) {
            seq_stack.pop();
            result += "-\n";
            arrow_idx++;
        }
    }

    cout << result;
    return 0;
}