#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main() {
    string s;
    cin >> s;

    stack<char> char_stack;

    int count = 0;

    for (int i = 0; i < s.size(); ++i) {
        char current = s[i];
        if (current == '(') {
            char_stack.push(current);
        } else { // c == ')'
            if (i > 0 && s[i-1] == '(') { // 레이저일 때
                char_stack.pop();
                count = count + char_stack.size();
            }
            else { // 막대기 끝 부분일 때
                count++;
                char_stack.pop();
            }
        }
    }

    cout << count << '\n';

    return 0;
}