#include <iostream>
#include <string>

using namespace std;

int queue[10001] = {0};
int begin_idx = 0;
int end_idx = 0;

int empty() {
    return begin_idx == end_idx;
}

void push(int x) {
    queue[end_idx++] = x;
}

int pop() {
    if (empty()) {
        return -1;
    }
    int result = queue[begin_idx++];
    return result;
}

int size() {
    return end_idx - begin_idx;
}

int front() {
    if (empty()) return -1;
    return queue[begin_idx];
}

int back() {
    if (empty()) return -1;
    return queue[end_idx-1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    string command;
    int input_num;

    while(N--) {
        cin >> command;
        if (command == "push") {
            cin >> input_num;
            push(input_num);
        }
        else if (command == "pop") {
            cout << pop() << "\n";
        }
        else if (command == "size") {
            cout << size() << "\n";
        }
        else if (command == "empty") {
            cout << empty() << "\n";
        }
        else if (command == "front") {
            cout << front() << "\n";
        }
        else if (command == "back") {
            cout << back() << "\n";
        }
    }

    return 0;
}
