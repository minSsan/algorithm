//? 구조체 사용 없이 visited 배열에 경로 값을 저장

#include<vector>
#include<queue>

#define WALL 0
#define ROAD 1

using namespace std;

int n, m;
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
int visited[100][100];

bool can_go(vector<vector<int>> &maps, int row, int col) {
    return (0 <= row && row < n) && (0 <= col && col < m) && maps[row][col] == ROAD && visited[row][col] == 0;
}

int solution(vector<vector<int> > maps)
{
    n = maps.size(); m = maps[0].size();
    int current_row, current_col, next_row, next_col, current_cnt;
    
    queue<pair<int, int>> q;
    q.push({0, 0});
    visited[0][0] = 1;
    
    while(!q.empty()) {
        current_row = q.front().first; current_col = q.front().second; 
        current_cnt = visited[current_row][current_col];
        q.pop();
        
        if (current_row == n-1 && current_col == m-1) {
            return current_cnt;
        }
        
        for (int i = 0; i < 4; ++i) {
            next_row = current_row + dr[i]; next_col = current_col + dc[i];
            if (can_go(maps, next_row, next_col)) {
                visited[next_row][next_col] = current_cnt+1;
                q.push({next_row, next_col});
            }
        }
    }
    
    return -1;
}