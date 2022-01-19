#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool isVPS(string str) {
    stack<char> left_parenthesis;
    for (char parenthesis : str) {
        if (parenthesis == '(') {
            left_parenthesis.push(parenthesis);
        }
        else if (parenthesis == ')') {
            if (left_parenthesis.empty()) {
                return false;
            }
            left_parenthesis.pop();
        }
    }
    if (left_parenthesis.empty()) {
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    string input;
    
    cin >> T;
    cin.ignore();

    while (T--) {
        getline(cin, input);
        
        if (isVPS(input)) {
            cout << "YES" << '\n';
        }
        else {
            cout << "NO" << '\n';
        }
    }

    return 0;
}