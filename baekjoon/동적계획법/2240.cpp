#include <iostream>
#include <algorithm>

using namespace std;

//? t초 시점에 n번 나무 밑에 있을 때까지 w번 움직였을 경우, 먹을 수 있는 최대 자두 양
int dp[1001][3][31];

int reverse_tree(int tree) {
    if (tree == 1) return 2;
    return 1;
}

int main() {
    int t, w;
    cin >> t >> w;

    fill(dp[0][0], dp[0][0] + (t + 1) * (w + 1) * 3, -1);

    //* 1번 위치에서 시작
    dp[0][1][0] = 0;
    
    for (int i = 1; i <= t; ++i) {
        int tree_num;
        cin >> tree_num;

        //? 1. 반대편 위치에서 온 경우
        for (int cnt = 0; cnt < w; ++cnt) {
            if (dp[i-1][reverse_tree(tree_num)][cnt] != -1) {
                dp[i][tree_num][cnt+1] = max(dp[i-1][reverse_tree(tree_num)][cnt] + 1, dp[i][tree_num][cnt+1]);
            }
        }
        for (int cnt = 0; cnt <= w; ++cnt) {
            //? 2. 반대편 위치에서 그대로 있는 경우
            if (dp[i-1][reverse_tree(tree_num)][cnt] != -1) {
                dp[i][reverse_tree(tree_num)][cnt] = max(dp[i-1][reverse_tree(tree_num)][cnt], dp[i][reverse_tree(tree_num)][cnt]);

            }
            //? 3. 떨어진 위치에 있었던 경우
            dp[i][tree_num][cnt] = max(dp[i][tree_num][cnt], dp[i-1][tree_num][cnt] + 1);
        }
    }

    int result = 0;
    for (int i = 0; i <= t; ++i) {
        for (int cnt = 0; cnt <= w; ++cnt) {
            for (int tree = 1; tree <= 2; ++tree) {
                if (dp[i][tree][cnt] > result) {
                    result = dp[i][tree][cnt];
                }
            }
        }
    }
    cout << result << '\n';

    return 0;
}