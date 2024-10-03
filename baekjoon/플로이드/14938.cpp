#include <iostream>

#define INF 1501

using namespace std;

int main() {
    int n, m, r; // m: 수색범위
    cin >> n >> m >> r;
    int items[n+1];
    for (int i = 1; i <= n; ++i) {
        cin >> items[i];
    }

    int min_len[n+1][n+1]; // i 구간부터 j 구간까지의 최단 경로
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) min_len[i][j] = 0;
            else min_len[i][j] = INF;
        }
    }

    for (int i = 0; i < r; ++i) {
        int a, b, l;
        cin >> a >> b >> l;
        min_len[a][b] = l;
        min_len[b][a] = l;
    }

    //* 1. 각 정점부터 다른 정점까지의 모든 최단거리 구하기 (이 과정에서 아이템 수 축적)
    for (int mid = 1; mid <= n; ++mid) {
        for (int start = 1; start <= n; ++start) {
            for (int end = 1; end <= n; ++end) {
                if (min_len[start][mid] + min_len[mid][end] < min_len[start][end]) {
                    min_len[start][end] = min_len[start][mid] + min_len[mid][end];
                }
            }
        }
    }
    
    int result = 0;
    for (int start = 1; start <= n; ++start) {
        int accum = 0;
        for (int end = 1; end <= n; ++end) {
            if (min_len[start][end] <= m) {
                accum += items[end];
            }
        }
        if (accum > result) result = accum;
    }

    cout << result << '\n';

    return 0;
}