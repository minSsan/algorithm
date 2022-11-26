#include <iostream>

using namespace std;

//? num % 1000 으로 다시 풀어보기

bool is666(int num) {
    // int count = 0;
    
    // while (num != 0) {
    //     if (num % 10 == 6) {
    //         count++;
    //     } else {
    //         count = 0;
    //     }
        
    //     if (count == 3) {
    //         return true;
    //     }

    //     num = num / 10;
    // }

    while (num != 0) {
        if (num % 1000 == 666) {
            return true;
        }
        num = num / 10;
    }

    return false;
}

int main() {
    int n;
    cin >> n;

    int count = 1;
    int num = 666;

    while (count != n) {
        num++;
        if (is666(num)) {
            count++;
        }
    }

    cout << num << '\n';

    return 0;
}