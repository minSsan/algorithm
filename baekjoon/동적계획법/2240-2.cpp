#include <iostream>

using namespace std;

int main() {
    const int OTHER_SIDE[3] = {0, 2, 1}; // n번 나무의 반대편 나무

    int t, w;
    cin >> t >> w;

    int dp[t+1][w+1][3]; //? t초 시점까지, w번 움직여서, n번 나무 아래에 위치할 때까지 얻을 수 있는 최대 자두 수
    fill(dp[0][0], dp[0][0] + (t+1) * (w+1) * 3, -1);

    dp[0][0][1] = 0; // 1번 나무 아래에서 시작

    for (int i = 0; i < t; ++i) {
        int tree;
        cin >> tree;
        for (int cnt = 0; cnt <= w; ++cnt) {
            for (int cur = 1; cur <= 2; ++cur) {
                if (dp[i][cnt][cur] == -1) continue;

                //? cur 위치에 떨어진 경우
                if (cur == tree) {
                    //* 이동하지 않음
                    dp[i+1][cnt][cur] = max(dp[i][cnt][cur] + 1, dp[i+1][cnt][cur]);
                }
                //? 반대편 위치에 떨어진 경우
                else {
                    //* 1. 이동하지 않은 경우
                    dp[i+1][cnt][cur] = max(dp[i][cnt][cur], dp[i+1][cnt][cur]);

                    //* 2. tree 위치로 이동한 경우
                    if (cnt != w) {
                        dp[i+1][cnt+1][tree] = max(dp[i][cnt][cur] + 1, dp[i+1][cnt+1][tree]);
                    }
                }
            }
        }
    }

    int result = 0;
    for (int cnt = 0; cnt <= w; ++cnt) {
        for (int cur = 1; cur <= 2; ++cur) {
            if (dp[t][cnt][cur] > result) result = dp[t][cnt][cur];
        }
    }
    cout << result << '\n';

    return 0;
}