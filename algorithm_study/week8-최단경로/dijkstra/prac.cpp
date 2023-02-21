#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int node_num; // ? 노드의 갯수
const int MAX = 2000000000;
int min_d[101]; // ? 각 노드에 도달하기 위한 최단경로
bool visited[101];

struct node
{
    int distance; // ? 해당 노드까지의 거리
    int number; // ? 연결된 노드 번호
};

vector<node> graph[101]; // ? 최소 1번 노드 ~ 최대 100번 노드까지 있다고 가정
// bool visited[101];

void dijkstra(int start) {
    min_d[start] = 0; // * 시작노드 -> 시작노드 까지의 거리는 0
    visited[start] = true; // * 방문 표시
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // ? 거리가 가까운 노드부터 방문하기 위해 최소힙 사용
    pq.push({0, start}); // * 시작 노드부터 탐색

    while (!pq.empty()) {
        int current_d = pq.top().first; // 시작 지점으로부터 현재 노드까지의 거리
        int current_node = pq.top().second; // 현재 노드
        pq.pop();

        for (int i = 0; i < graph[current_node].size(); ++i) { // * 현재 노드와 연결된 모든 노드를 탐색한다.
            int next_node = graph[current_node][i].number;
            int next_d = graph[current_node][i].distance;

            if (!visited[next_node] && current_d + next_d < min_d[next_node]) {
                min_d[next_node] = current_d + next_d;
                pq.push({current_d + next_d, next_node});
            }
        }
    }
}

// ? {6, 5}, {}

int main() {
    int line_num;
    cin >> node_num >> line_num;

    for (int i = 0; i < 101; ++i) {
        min_d[i] = MAX;
    }

    for (int i = 0; i < line_num; ++i) {
        int start, end, distance; // ? 시작 노드, 도착 노드, 거리
        cin >> start >> end >> distance;
        graph[start].push_back({distance, end});
        graph[end].push_back({distance, start});
    }

    dijkstra(1); // 1번 노드부터 탐색 시작

    for (int i = 1; i <= node_num; ++i) {
        cout << min_d[i] << '\n';
    }

    return 0;
}