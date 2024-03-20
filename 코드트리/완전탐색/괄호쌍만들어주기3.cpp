#include <iostream>
#include <string>

using namespace std;

int main() {
    string input_str;
    cin >> input_str;

    int cnt = 0;
    // i번째 괄호와 쌍을 이룰 수 있는 경우의 수
    for (int i = 0; i < input_str.size()-1; ++i) {
        if (input_str[i] == ')') continue;
        // i번째 괄호와 쌍을 이룰 j번째 괄호
        for (int j = i; j < input_str.size(); ++j) {
            if (input_str[j] == ')') ++cnt;
        }
    }

    cout << cnt << '\n';

    return 0;
}