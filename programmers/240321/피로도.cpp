#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 각 던전을 탐험하기 위한 조건:   (현재 피로도 >= 최소 피로도)
// 각 던전을 탐험하고 난 후:      (현재 피로도 = 현재 피로도 - 소모 피로도)
// 유저가 최대한 탐험할 수 있는 최대 던전 수

//? 그리디 전제를 설정하기에는 현재 피로도와 최소 피로도 사이의 연관성이 없음
//?     최소 피로도 기준으로 먼저 방문? -> 최소 피로도가 크다고 소모 피로도가 적은가? (X)
//?     소모 피로도 기준으로 먼저 방문? -> 소모 피로도가 작은 것부터 방문하면, 이후 최소 피로도가 큰 것은 방문하지 못 할 수 있다.
//? 던전의 크기가 최대 8인 것을 미루어 보았을 때, 모든 경우를 따져서 가장 많이 방문할 수 있는 순서를 정한다.

vector<vector<int>> coord; // 방문 순서
bool visited[8]; // n번째 던전의 순서배정 여부
int dun_size;

void dfs(vector<int> v) {
    if (v.size() == dun_size) {
        coord.push_back(v);
        return ;
    }
    
    for (int i = 0; i < dun_size; ++i) {
        if (!visited[i]) { // i번째 던전을 아직 순서배정하지 않았다면
            visited[i] = true;
            v.push_back(i);
            dfs(v);
            v.pop_back();
            visited[i] = false;
        }
    }
}

// v: 방문 순서 인덱스
int cnt_visit(int tired, vector<vector<int>> &dungeons, vector<int> v) {
    int cnt = 0;
    for (int i = 0; i < v.size(); ++i) {
        vector<int> dungeon = dungeons[v[i]];
        if (tired < dungeon[0]) {
            return cnt;
        }
        
        cnt++;
        tired -= dungeon[1];
    }
    return cnt;
}

// k: 현재 피로도(1<= k <= 5000), dungeons(<= 8): [최소 피로도, 소모 피로도]의 배열
// 최소 피로도 >= 소모 피로도
int solution(int k, vector<vector<int>> dungeons) {
    int answer = -1;
    int max_visit = 0; // 최대 방문 수
    dun_size = dungeons.size();
    
    // 1. 후보군 설정
    dfs({});
    
    // 2. 모든 후보군에 대해 방문 가능한 던전 수를 구하고, 최댓값을 구한다.
    for (int i = 0; i < coord.size(); ++i) {
        max_visit = max(max_visit, cnt_visit(k, dungeons, coord[i]));
    }
    
    return max_visit;
}