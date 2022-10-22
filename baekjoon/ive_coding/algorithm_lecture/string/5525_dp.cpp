#include <iostream>
#include <string>

using namespace std;

int main() {
    int n, m;
    cin >> n; // Pn에서 사용 될 n
    cin >> m; // 글자 수
    int result = 0;

    string s;
    cin >> s;

    int interval = 2 * n;
    int count[s.size()];

    for (int i = 0; i < s.size(); ++i) {
        count[i] = 0;
    }

    // * Pn 만들기
    string Pn = "";
    for (int i = 0; i < 2 * n + 1; ++i) {
        if (i % 2 == 0) {
            Pn.push_back('I');
        } else {
            Pn.push_back('O');
        }
    }

    for (int i = 0; i < m - interval; ++i) {
        if (s[i] == 'O' && i > 0) {
            count[i] = count[i-1];
            continue;
        }

        if (s.substr(i, Pn.size()) == Pn) {
            if (i > 0) {
                count[i] = count[i-1] + 1;
            } else {
                count[i] = 1;
            }
        } else if (i > 0) {
            count[i] = count[i-1];
        }

    }

    return 0;
}