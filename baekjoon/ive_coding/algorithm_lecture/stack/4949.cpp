#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
    string s;
    stack<char> paren; // parentheses

    bool isBalance = true;

    getline(cin, s);

    while (s != ".") {
        // * 스택 초기화
        while (!paren.empty()) {
            paren.pop();
        }

        // * 균형 참/거짓 변수 초기화
        isBalance = true;

        for (char c : s) {
            if (c == '(' || c == '[') {
                paren.push(c);
            } else if (c == ')') {
                if (!paren.empty() && paren.top() == '(') {
                    paren.pop();
                }
                else {
                    isBalance = false;
                }
            } else if (c == ']') {
                if (!paren.empty() && paren.top() == '[') {
                    paren.pop();
                }
                else {
                    isBalance = false;
                }
            }
        }

        if (!paren.empty()) {
            isBalance = false;
        }
        
        if (isBalance) {
            cout << "yes\n";
        } else {
            cout << "no\n";
        }

        getline(cin, s);
    }

    return 0;
}