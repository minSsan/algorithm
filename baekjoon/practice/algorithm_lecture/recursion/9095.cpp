#include <iostream>

using namespace std;

int n, cnt;

void recursion(int sum) {
    if (sum == n) {
        cnt++;
        return ;
    }
    
    if (sum + 1 <= n) recursion(sum + 1);
    if (sum + 2 <= n) recursion(sum + 2);
    if (sum + 3 <= n) recursion(sum + 3);
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        cin >> n;

        recursion(0);

        cout << cnt << '\n';

        cnt = 0;
    }

    return 0;
}