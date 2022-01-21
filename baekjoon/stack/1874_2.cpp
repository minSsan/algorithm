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

    int input_num = 1;
    int current;
    for (int i = 0; i < n; ++i) {
        cin >> current;
        if (!seq_stack.empty() && current < seq_stack.top()) {
            cout << "NO\n";
            return 0;
        }

        while (input_num <= current) {
            seq_stack.push(input_num);
            result += "+\n";
            input_num++;
        }
        seq_stack.pop();
        result += "-\n";
    }

    cout << result;

    return 0;
}