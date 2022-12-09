#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ? 문자열과, 각 문자별로 문자를 뺄 때 드는 cost가 할당된 배열이 들어올때, 가장 작은 비용으로 글자가 겹치지 않게 할 때의 cost를 출력하시오

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    string s;
    cin >> s;

    vector<int> cost(s.length());
    int result = 0;

    for (int i = 0; i < s.length(); ++i) {
        cin >> cost[i];
    }

    for (int i = 0; i < s.length() - 1; ++i) {
        if (s[i] == s[i+1]) {
            result += cost[i] < cost[i+1] ? cost[i] : cost[i+1];
        }
    }

    cout << result << '\n';

    return 0;
}