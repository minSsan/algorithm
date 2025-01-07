#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string s;
    cin >> s;

    int cnt[2];
    fill(cnt, cnt+2, 0);
    char cur = s[0];

    cnt[cur - '0'] = 1;
    for (char c : s) {
        if (c != cur) {
            cur = c;
            cnt[cur - '0']++;
        }
    }

    sort(cnt, cnt+2);

    cout << cnt[0] << '\n';

    return 0;
}