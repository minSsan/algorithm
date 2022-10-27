#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isHigher(char a, char b) { // a가 b보다 우선순위 높냐?
    if (a == '*' || a == '/') {
        return true;
    }
    else if (b == '*' || b == '/') {
        return false;
    }
    else {
        return true;
    }
}

int main() {
    string input_s;
    string output_s;
    cin >> input_s;

    stack<char> operator_stack;
    char current_char;

    for (int i; i < input_s.size(); ++i) {
        current_char = input_s[i];
        if (current_char >= 'A' && current_char <= 'Z') {
            output_s.push_back(current_char);
        }
        else if (current_char != '(' && current_char != ')') {
            if (!operator_stack.empty() && isHigher(current_char, operator_stack.top())) {
                
            }
        }
    }

    return 0;
}