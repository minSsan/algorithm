#include <string>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int bound;
bool visited[10000];
int total;

vector<vector<int>> cases;

// v: 방향 바꾸는 명함 인덱스 목록
void dfs(vector<int> v) {
    if (v.size() == bound) {
        cases.push_back(v);
        return ;
    }
    
    for (int i = 0; i < total; ++i) {
        if (!visited[i]) {
            v.push_back(i);
            visited[i] = true;
            dfs(v);
            v.pop_back();
            visited[i] = false;
        }
    }
}

// v: 명함 목록
int get_size(vector<vector<int>> v) {
    int w_max = 0, h_max = 0;
    for (int i = 0; i < v.size(); ++i) {
        w_max = max(w_max, v[i][0]);
        h_max = max(h_max, v[i][1]);
    }
    return w_max * h_max;
}

// 모든 명함을 수납할 수 있으면서도, 최대한 작은 지갑의 크기를 구해야 함
// 단, 명함의 수납 방향을 변경할 수 있음
// ? 가로로 눕힐 명함을 탐색한다. 
// ? ex. (1), (2), (3), (4), (1, 2), (1, 3), (1, 4), (2, 3), ...
int solution(vector<vector<int>> sizes) {
    int answer = 0;
    total = sizes.size();
    
    // bound: 가로로 눕힐 명함 수
    // case 값 설정
    for (bound = 0; bound < total; ++bound) {
        dfs({});
    }
    
    int min_size = INT_MAX;
    
    // 각 케이스에 대해
    for (int i = 0; i < cases.size(); ++i) {
        vector<vector<int>> v(sizes.begin(), sizes.end());
        // i번째 케이스에 있는 모든 명함들을 뒤집는다. 
        for (int j = 0; j < cases[i].size(); ++j) {
            int index = cases[i][j];
            int tmp = sizes[index][0];
            sizes[index][0] = sizes[index][1];
            sizes[index][1] = tmp;
        }
        min_size = min(min_size, get_size(v));
    }
    
    answer = min_size;
    
    return answer;
}