#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string s[100];

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> s[i];
        // 입력받은 문장 하나를 사전 순으로 정렬
        sort(s[i].begin(), s[i].end());
    }

    // 입력받은 문장들을 사전 순으로 정렬
    sort(s, s+n);

    for (int i = 0; i < n; ++i) {
        cout << s[i] << '\n';
    }

    return 0;
}