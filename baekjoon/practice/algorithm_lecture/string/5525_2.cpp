#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n; // Pn에서 사용 될 n
    cin >> m; // 글자 수

    string s;
    cin >> s;

    int len = 0;
    int flag = 0;
    int result = 0;
    vector<int> count(m, 0);
    
    for (int i = 0; i < m; ++i) {
        // * I 바로 앞에 O
        if (s[i] == 'I' && flag == 0) {
            flag = 1;
            len++;
        }

        // * O 바로 앞에 I
        else if (s[i] == 'O' && flag == 1) { 
            flag = 0;
            len++;
        }

        // * 그냥 I이거나 | 같은 문자가 연속해서 나온 경우 (II)
        else if (s[i] == 'I') {
            len = 1;
            flag = 1;
        }

        // * 그냥 O이거나 | 같은 문자가 연속해서 나온 경우 (OO)
        else {
            flag = 0;
            len = 0;
        }

        if (s[i] == 'I' && len >= 2 * n + 1) {
            count[i - (2 * n)] = 1;
        }
    }

    for (int i = 0; i < m; ++i) {
        result = result + count[i];
    }

    cout << result << '\n';

    return 0;
}