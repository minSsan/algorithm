#include <iostream>
using namespace std;

int biggest(int a, int b, int c) {
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c;
    cin >> a >> b >> c;
    if (a == b) {
        if (a == c) { // 모두 같은 눈
            cout << 10000 + a * 1000;
        }
        else {
            cout << 1000 + a * 100;
        }
    }
    else if (a == c) {
        cout << 1000 + a * 100;
    }
    else if (b == c) {
        cout << 1000 + b * 100;
    }
    else {
        
    }

    return 0;
}