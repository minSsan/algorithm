#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string input;
    cin >> input;

    stack<char> left;
    stack<char> right;

    for (char c : input) {
        left.push(c);
    }

    int M;
    cin >> M;
    char command, input_char;

    while (M--) {
        cin >> command;
        if (command == 'L' && !left.empty()) {
            right.push(left.top());
            left.pop();
        }
        else if (command == 'D' && !right.empty()) {
            left.push(right.top());
            right.pop();
        }
        else if (command == 'B' && !left.empty()) {
            left.pop();
        }
        else if (command == 'P') {
            cin >> input_char;
            left.push(input_char);
        }
    }

    while (!left.empty()) {
        right.push(left.top());
        left.pop();
    }

    while (!right.empty()) {
        cout << right.top();
        right.pop();
    }

    return 0;
}