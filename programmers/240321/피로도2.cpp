#include <string>
#include <vector>

using namespace std;

bool visited[8];
int max_cnt;

void dfs(int cnt, int tired, vector<vector<int>>& dungeons) {
    if (cnt > max_cnt) max_cnt = cnt;
    
    for (int i = 0; i < dungeons.size(); ++i) {
        if (!visited[i] && tired >= dungeons[i][0]) {
            visited[i] = true;
            dfs(cnt+1, tired-dungeons[i][1], dungeons);
            visited[i] = false;
        }
    }
}

int solution(int k, vector<vector<int>> dungeons) {
    int answer = -1;
    
    dfs(0, k, dungeons);
    
    answer = max_cnt;
    
    return answer;
}