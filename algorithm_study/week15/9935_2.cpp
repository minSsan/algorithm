#include <iostream>
#include <string>

using namespace std;

// * 폭발 문자열을 발견할 시 폭발 문자열을 제거 -> 앞, 뒤로 합침
// * 폭발 문자열을 제거한 후의 결과는?

int main() {
    string message, explosion;
    cin >> message >> explosion;

    int dp[1000000] = {0,};
    int include[1000000];

    for (int i = 0; i < 1000000; ++i) {
        include[i] = 1;
    }

    if (message[0] == explosion[0]) dp[0] = 1;

    for (int i = 1; i < message.size(); ++i) {
        int next_index = dp[i-1];
        if (explosion[next_index] == message[i]) {
            dp[i] = next_index + 1;
        } else if (explosion[0] == message[i]) {
            dp[i] = 1;
        }

        if (dp[i] == explosion.size()) {
            include[i] = 0;
            int cnt = 1, index = i-1;
            while (index >= 0 && cnt < explosion.size()) {
                if (dp[index] > 0 && include[index] == 1) {
                    include[index] = 0;
                    cnt++;
                }
                --index;
            }
            
            if (index >= 0) {
                dp[i] = dp[index];
            } else {
                dp[i] = 0;
            }
        }
    }

    string result = "";
    for (int i = 0; i < message.size(); ++i) {
        if (include[i]) {
            result += message[i];
        }
    }

    if (result.size() > 0) {
        cout << result << '\n';
    } else {
        cout << "FRULA\n";
    }

    return 0;
}