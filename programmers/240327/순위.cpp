#include <string>
#include <vector>
#include <iostream>

using namespace std;

// [
//     [0,  1,  0,  0,  0]
//     [-1, 0, -1, -1,  1]
//     [0,  1,  0, -1,  0]
//     [0,  1,  1,  0,  0]
//     [0, -1,  0,  0,  0]
// ]

// [
//     [0,  1,  0,  0,  1]
//     [-1, 0, -1, -1,  1]
//     [0,  1,  0, -1,  1]
//     [0,  1,  1,  0,  1]
//     [-1,-1, -1, -1,  0]
// ]

//? graph[a][b] -> -1 : a선수가 b선수보다 못한다.
//?             -> 1  : a선수가 b선수보다 잘한다.
//?             -> 0  : 서로의 실력을 모른다.

int graph[101][101];

// results: [A, B] -> A선수가 B선수를 이김
// 1 <= n <= 100, 1 <= results.size() <= 4500
int solution(int n, vector<vector<int>> results) {
    int answer = 0;
    
    int better, worse;
    for (int i = 0; i < results.size(); ++i) {
        better = results[i][0];
        worse = results[i][1];
                
        // 그래프 기록
        graph[better][worse] = 1;
        graph[worse][better] = -1;
    }
    
    // 각 선수가 실력을 알고있는 선수 조사
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                if (graph[i][j] != 0 && graph[i][j] == graph[j][k]) {
                    graph[i][k] = graph[i][j];
                }
                if (graph[j][i] != 0 && graph[j][i] == graph[i][k]) {
                    graph[j][k] = graph[j][i];
                }
            }
        }
    }
    
    for (int i = 1; i <= n; ++i) {
        int cnt = 0;
        for (int j = 1; j <= n; ++j) {
            if (graph[i][j] != 0) ++cnt;
        }
        if (cnt == n-1) ++answer;
    }
    
    return answer;
}