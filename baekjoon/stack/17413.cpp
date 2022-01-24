#include <iostream>
#include <string>
#include <stack>

using namespace std;

void print(stack<char> &stack) {
    while(!stack.empty()) {
        cout << stack.top();
        stack.pop();
    }
}

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
            print(char_stack);
        }

        if (flag) {
            cout << c;
        }
        else {
            if (c == ' ') {
                print(char_stack);
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

    print(char_stack);

    return 0;
}