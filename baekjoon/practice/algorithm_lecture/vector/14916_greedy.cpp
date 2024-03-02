#include <iostream>
#include <vector>

using namespace std;

int main() {
    // 2원짜리, 5원짜리
    int n;
    cin >> n;

    int result = 0;

    while (n > 0) {
        if (n % 5 == 0) {
            result = result + n / 5;
            n = 0;
        } else{
            result++;
            n = n-2;
        } 
    }
    if (n < 0) cout << -1 << '\n';
    else cout << result << '\n';

    return 0;
}