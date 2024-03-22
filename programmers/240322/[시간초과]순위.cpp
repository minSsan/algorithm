#include <string>
#include <vector>
#include <iostream>

using namespace std;

// 1번 ~ n번까지의 선수가 대회에 참여
//? 명확하게 순위를 매길 수 있는 선수의 숫자를 리턴

//? 연결 관계를 그래프로 표현한 후, 이를 dfs로 탐색해서 방문된 선수의 수를 기록한다.
//?      -> 각 선수마다, 각 선수의 위/아래를 따로 검사한다.

int know[101]; // n번 선수가 알고있는 선수의 수
vector<int> better[101]; // n번 선수보다 잘하는 선수 목록
vector<int> worse[101]; // n번 선수보다 못하는 선수 목록
bool visited[101];

void init_visited(int n) {
    for (int i = 1; i <= n; ++i) visited[i] = false;
}

void better_dfs(int n) {
    visited[n] = true;
    if (better[n].size() == 0) return ;
    
    for (int i = 0; i < better[n].size(); ++i) {
        better_dfs(better[n][i]);
    }
}

void worse_dfs(int n) {
    visited[n] = true;
    if (worse[n].size() == 0) return ;
    
    for (int i = 0; i < worse[n].size(); ++i) {
        worse_dfs(worse[n][i]);
    }
}

int get_know(int n) {
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (visited[i]) ++cnt;
    }
    return cnt;
}

// results: [A, B] -> A선수가 B선수를 이김
// 1 <= n <= 100, 1 <= results.size() <= 4500
int solution(int n, vector<vector<int>> results) {
    int answer = 0;
    
    int b, w;
    for (int i = 0; i < results.size(); ++i) {
        b = results[i][0]; w = results[i][1];
        better[w].push_back(b);
        worse[b].push_back(w);
    }
    
    // 1번부터 n번 선수까지 순회하면서, 각 선수가 알고있는 선수의 수를 기록
    // 1. better, worse를 DFS 탐색하여 기록한다.
    for (int i = 1; i <= n; ++i) {
        better_dfs(i);
        know[i] += (get_know(n)-1);
        init_visited(n);
        
        worse_dfs(i);
        know[i] += (get_know(n)-1);
        init_visited(n);
    }
        
    for (int i = 1; i <= n; ++i) {
        cout << i << "가 알고있는 선수의 수: " << know[i] << '\n';
    }
    
    for (int i = 1; i <= n; ++i) {
        if (know[i] == n-1) ++answer;
    }
    
    return answer;
}