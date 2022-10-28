#include <iostream>
#include <stack>
#include <string>

using namespace std;

int compare(char a, char b) {
    if (a == '*' || a == '/') {
        if (b == '+' || b == '-') {
            return 1; // a가 더 높다
        }
        else {
            return 0; // 우선순위 같다
        }
    } else {
        if (b == '+' || b == '-') {
            return 0; // 우선순위 같다
        }
        else {
            return -1; // a가 더 낮다
        }
    }
}

int main() {
    string input_s;
    string output_s;
    cin >> input_s;

    stack<char> operator_stack;

    int flag = 0; // 연산자를 붙여야 하는지 확인하는 변수

    for (char current : input_s) {
        // * 괄호
        if (current == '(') {
            if (flag == 1) {
                flag = 0;
            }
            operator_stack.push(current);
        } else if (current == ')') {
            while (operator_stack.top() != '(') {
                output_s.push_back(operator_stack.top());
                operator_stack.pop();
            }
            operator_stack.pop();

        // * 피연산자
        } else if (current >= 'A' && current <= 'Z') {
            output_s.push_back(current);
            if (!operator_stack.empty() && operator_stack.top() != '(' && flag == 1) {
                output_s.push_back(operator_stack.top());
                operator_stack.pop();
                flag = 0;
            }

        // * 연산자
        } else {
            if (!operator_stack.empty() && operator_stack.top() != '(') {
                if (compare(current, operator_stack.top()) <= 0) { // 우선순위 같거나 낮을 때
                    output_s.push_back(operator_stack.top());
                    operator_stack.pop();
                }
                else { // 우선순위 높을 때
                    flag = 1;
                }
            }
            operator_stack.push(current);
        }
    }

    while (!operator_stack.empty()) {
        output_s.push_back(operator_stack.top());
        operator_stack.pop();
    }

    cout << output_s << '\n';

    return 0;
}