#include <iostream>
#include <string>

using namespace std;

int arr[10001] = {0};
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
        return -1;
    }
    int tmp = arr[arr_size-1];
    arr[arr_size-1] = 0;
    arr_size--;
    return tmp;
}

int top() {
    if (arr_size == 0) {
        return -1;
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

    int N, input_num;
    string command;
    cin >> N;

    while (N--) {
        cin >> command;
        if (command == "push") {
            cin >> input_num;
            push(input_num);
        } 
        else if (command == "top") {
            cout << top() << '\n';
        }
        else if (command == "size") {
            cout << size() << '\n';
        }
        else if (command == "empty") {
            cout << empty() << '\n';
        }
        else if (command == "pop") {
            cout << pop() << '\n';
        }
    }

    return 0;
}