#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

// 1번 노드로부터 가장 멀리 떨어진(= 사이 간선 수가 가장 많은) 노드가 몇 개인지 리턴

vector<int> graph[20001]; // n번 노드와 연결된 노드 배열
int _distance[20001] = {-1, }; // 1번 노드 ~ n번 노드 사이의 거리
int cnt, max_dist;

void bfs(int start_node) {
    for (int i = 0; i < 20001; ++i) _distance[i] = -1;
    
    queue<int> q; // 노드 번호
    
    _distance[start_node] = 0;
    q.push(start_node);
    
    while (!q.empty()) {
        int current_node = q.front(); 
        int dist = _distance[current_node]; 
        q.pop();
        
        if (dist > max_dist) {
            max_dist = dist;
            cnt = 1;
        } else if (dist == max_dist) ++cnt;
        
        // 현재 노드와 연결된 다른 노드를 모두 탐색
        for (int i = 0; i < graph[current_node].size(); ++i) {
            if (_distance[graph[current_node][i]] == -1) {
                q.push(graph[current_node][i]);
                _distance[graph[current_node][i]] = dist + 1;
            }
        }
    }
}

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    // 1. graph 배열 셋업 - 연결 관계 표시
    for (int i = 0; i < edge.size(); ++i) {
        int start = edge[i][0]; int end = edge[i][1];
        graph[start].push_back(end);
        graph[end].push_back(start);
    }
    
    bfs(1);
    
    answer = cnt;
    
    return answer;
}