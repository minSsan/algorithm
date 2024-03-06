//? 구조체를 사용하여 경로 값 기록

#include<vector>
#include<queue>

#define WALL 0
#define ROAD 1

using namespace std;

int n, m;
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
bool visited[100][100];

struct node {
    int row;
    int col;
    int cnt;
};

bool can_go(vector<vector<int>> &maps, int row, int col) {
    return (0 <= row && row < n) && (0 <= col && col < m) && maps[row][col] == ROAD && !visited[row][col];
}

int solution(vector<vector<int> > maps)
{
    n = maps.size(); m = maps[0].size();
    
    int current_row, current_col, next_row, next_col, current_cnt;
    
    queue<node> q;
    q.push({0, 0, 1});
    
    while(!q.empty()) {
        current_row = q.front().row; current_col = q.front().col; 
        current_cnt = q.front().cnt;
        q.pop();
        
        if (current_row == n-1 && current_col == m-1) {
            return current_cnt;
        }
        
        for (int i = 0; i < 4; ++i) {
            next_row = current_row + dr[i]; next_col = current_col + dc[i];
            if (can_go(maps, next_row, next_col)) {
                visited[next_row][next_col] = true;
                q.push({next_row, next_col, current_cnt+1});
            }
        }
    }
    
    return -1;
}