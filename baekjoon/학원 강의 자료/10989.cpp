#include <iostream>

using namespace std;

int num[10001] = {0};

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    
    int input;
    for (int i = 0; i < n; ++i) {
        cin >> input;
        num[input]++;
    }

    for (int i = 1; i <= 10000; ++i) {
        for (int j = 0; j < num[i]; ++j) {
            cout << i << '\n';
        }
    }

    return 0;
}