#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// * 방향그래프가 주어지면 주어진 시작점에서 다른 모든 정점으로의 최단 경로를 구하는 프로그램을 작성하시오. 단, 모든 간선의 가중치는 10 이하의 자연수이다.
// * 모든 정점에는 1부터 V까지 번호가 매겨져 있다
// ! 서로 다른 두 정점 사이에 여러 개의 간선이 존재할 수도 있음

int v, e; // ? v: 정점의 갯수, e: 간선의 갯수
int k; // ? k: 시작 정점의 번호
const int INF = 300000 * 10;

struct node
{
    int cost;
    int number;
};

vector<node> graph[20001]; // 1 ~ v 각 정점 간의 연결 관계를 나타내는 배열
int min_d[20001]; // 1 ~ v의 각 정점까지 도달하는 최단 거리
// bool visited[20001]; // ! 간선끼리 경로가 여러 개 존재할 수 있기 때문에, 방문처리는 생략해도 된다. -> 방문처리를 해버리면 여러가지 경로를 모두 살펴볼 수 없음.

void dijkstra(int start) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    min_d[start] = 0; // 시작점 ~ 시작점 거리는 0
    // visited[start] = true;
    pq.push({0, start});

    while (!pq.empty()) {
        int now_cost = pq.top().first; // 현재 노드에 도달하는 최단 거리
        int now_num = pq.top().second; // 현재 노드 번호 
        // visited[now_num] = true;
        pq.pop();

        // 현재 노드와 연결된 모든 노드를 탐색
        for (int i = 0; i < graph[now_num].size(); ++i) {
            int next_num = graph[now_num][i].number; // 다음 노드 번호
            int next_cost = now_cost + graph[now_num][i].cost; // 다음 노드에 도달하는 최단 거리
            if (next_cost < min_d[next_num]) {
                min_d[next_num] = next_cost;
                pq.push({next_cost, next_num});
            }
        }
    }
}

int main() {
    cin >> v >> e;
    cin >> k;

    for (int i = 1; i <= v; ++i) {
        min_d[i] = INF;
    }

    int start, end, cost; // ? start: 시작 정점, end: 도착 정점, cost: 가중치
    for (int i = 0; i < e; ++i) {
        cin >> start >> end >> cost;
        graph[start].push_back({cost, end});
    }

    dijkstra(k);

    for (int i = 1; i <= v; ++i) {
        if (min_d[i] == INF) {
            cout << "INF\n";
        } else {
            cout << min_d[i] << '\n';
        }
    }

    return 0;
}