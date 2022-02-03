#include <iostream>
#include <string>
#include <stack>

using namespace std;

int arr[100000] = {0};
int arr_size = 0;

void push(int x) {
    arr[arr_size] = x;
    arr_size++;
}

bool empty() {
    return arr_size == 0;
}

int pop() {
    if (empty()) {
        return 0;
    }
    int tmp = arr[arr_size-1];
    arr[arr_size-1] = 0;
    arr_size--;
    return tmp;
}

int top() {
    if (arr_size == 0) {
        return 0;
    } else {
        return arr[arr_size-1];
    }
}

int size() {
    return arr_size;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string input_str;
    cin >> input_str;
    stack<char> s;

    char prev = NULL;

    int result = 0;
    int tmp;

    for (char c : input_str) {
        if (prev == '(' && c == ')') { // laser
            s.pop();
            pop();

            tmp = pop() + 1;
            push(tmp);
        }
        else if (c == '(') {
            s.push(c);
            push(0);
        }
        else if (c == ')') {
            s.pop();
            tmp = pop();
            result += tmp + 1;
            
            if (!empty()) {
                tmp += pop();
                push(tmp);
            }
        }

        prev = c;
    }

    cout << result;

    return 0;
}