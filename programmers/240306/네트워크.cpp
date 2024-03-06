#include <string>
#include <vector>

using namespace std;

bool visited[200];

// computer와 연결된 다른 컴퓨터를 모두 방문하는 함수
void dfs(vector<vector<int>> &computers, int computer) {
    visited[computer] = true;
    for (int i = 0; i < computers[computer].size(); ++i) {
        if (computers[computer][i] && !visited[i]) dfs(computers, i);
    }
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    
    for (int i = 0; i < computers.size(); ++i) {
        for (int j = 0; j < computers[i].size(); ++j) {
            if (computers[i][j] == 1 && !visited[j]) {
                ++answer;
                dfs(computers, j);
            }
        }
    }
    
    return answer;
}