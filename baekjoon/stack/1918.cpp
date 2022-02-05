// (1) .top()과 우선순위 동일한 경우: top() 출력 후 현재 연산자 push
// (2) .top()보다 우선순위 높은 경우: flag true , push -> 다음 알파벳 출력시 flag 검사
//      -> 알파벳 출력시 flag true면 알파벳 출력 후 .top() 출력 & pop()
// (3) .top()보다 우선순위 낮은 경우: .top() 출력 & pop() push()

#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool isHigher(char a, char b) {
    if (a == '+' || a == '-') {
        return false;
    }
    else {
        if (b == '+' || b == '-') {
            return true;
        }
        return false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string text;
    cin >> text;

    stack<char> operator_stack;
    bool flag = false;
    bool parentheses = false;

    for (char c : text) {
        if (c == '(') {
            parentheses = true;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            // operator_stack.push(c);
            if (!operator_stack.empty() && !parentheses) {
                if (c == operator_stack.top() || !isHigher(c, operator_stack.top())) {
                    cout << operator_stack.top();
                    operator_stack.pop();
                }
                else {
                    flag = true;
                }
            } 
            operator_stack.push(c);
        }
        else if (c == ')') {
            cout << operator_stack.top();
            operator_stack.pop();
        }
        else if (c >= 'A' && c <= 'Z') {
            cout << c;
            if (flag) {
                cout << operator_stack.top();
                operator_stack.pop();
                flag = false;
            }
        }
    }

    while (!operator_stack.empty()) {
        cout << operator_stack.top();
        operator_stack.pop();
    }

    return 0;
}