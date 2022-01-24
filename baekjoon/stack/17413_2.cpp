#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string input_str;
    stack<char> char_stack;
    bool flag = false;

    getline(cin, input_str);

    for (char c : input_str) {
        if (c == '<') {
            flag = true;
            while (!char_stack.empty()) {
                cout << char_stack.top();
                char_stack.pop();
            }
        }

        if (flag) {
            cout << c;
        }
        else {
            if (c == ' ') {
                while (!char_stack.empty()) {
                    cout << char_stack.top();
                    char_stack.pop();
                }
                cout << c;
            }
            else {
                char_stack.push(c);
            }
        }

        if (c == '>') {
            flag = false;
        }
    }

    while (!char_stack.empty()) {
        cout << char_stack.top();
        char_stack.pop();
    }

    return 0;
}