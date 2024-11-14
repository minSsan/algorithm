#include <iostream>
#include <string>

using namespace std;

int main() {
    string input;
    cin >> input;
    int dp[input.size()][27]; //? dp[i][n]: i번째 글자까지, n번째 문자로 끝나는 문자열의 개수
    fill(dp[0], dp[0] + input.size() * 27, 0);

    dp[0][input[0] - '0'] = 1;

    for (int i = 1; i < input.size(); ++i) {
        int cur = input[i] - '0';
        for (int prev = 1; prev <= 26; ++prev) {
            if (dp[i-1][prev] == 0) continue;
            //* 1. 현재 문자를 그대로 해석하는 것
            dp[i][cur] = dp[i][cur] % 1000000 + dp[i-1][prev] % 1000000;
            //* 2. 현재 문자를 앞 문자와 합쳐서 해석하는 것
            if (prev * 10 + cur <= 26) {
                dp[i][prev * 10 + cur] = dp[i][prev * 10 + cur] + dp[i-1][prev] % 1000000;
            }
        }
    }

    int result = 0;
    for (int i = 1; i <= 26; ++i) {
        result = result % 1000000 + dp[input.size()-1][i] % 1000000;
    }
    cout << result << '\n';

    return 0;
}