#include <iostream>
#include <vector>
#include <queue>

#define INF 160000001

using namespace std;

int main() {
    int n, e;
    cin >> n >> e;

    vector<pair<int, int>> graph[n+1]; // {정점 번호, 거리}

    for (int i = 0; i < e; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
        graph[b].push_back({a, c});
    }

    int v1, v2;
    cin >> v1 >> v2;

    //* 1. 1번 정점에서 각 정점까지의 거리 구하기
    int d[n+1]; // 1번 정점 ~ i번 정점까지 최단거리
    fill(d, d+n+1, INF); d[1] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // {거리, 정점 번호}
    pq.push({0, 1});

    while (!pq.empty()) {
        int cur_dist = pq.top().first;
        int cur_node = pq.top().second;
        pq.pop();

        if (cur_dist != d[cur_node]) {
            continue;
        }

        for (pair<int, int> info : graph[cur_node]) {
            int next_node = info.first;
            int dist = info.second;
            if (cur_dist + dist < d[next_node]) {
                d[next_node] = cur_dist + dist;
                pq.push({cur_dist + dist, next_node});
            }
        }
    }

    int v1_dist = d[v1]; // 1 ~ v1까지의 거리
    int v2_dist = d[v2]; // 1 ~ v2까지의 거리

    //* 2-1. v1을 먼저 방문해서 n번 정점에 도착하는 경우
    fill(d, d+n+1, INF); d[v1] = 0;
    pq.push({0, v1});

    while (!pq.empty()) {
        int cur_dist = pq.top().first;
        int cur_node = pq.top().second;
        pq.pop();

        if (cur_dist != d[cur_node]) {
            continue;
        }

        for (pair<int, int> info : graph[cur_node]) {
            int next_node = info.first;
            int dist = info.second;
            if (cur_dist + dist < d[next_node]) {
                d[next_node] = cur_dist + dist;
                pq.push({cur_dist + dist, next_node});
            }
        }
    }

    v1_dist += d[v2]; // 1 ~ v1 + v1 ~ v2

    fill(d, d+n+1, INF); d[v2] = 0;
    pq.push({0, v2});

    while (!pq.empty()) {
        int cur_dist = pq.top().first;
        int cur_node = pq.top().second;
        pq.pop();

        if (cur_dist != d[cur_node]) {
            continue;
        }

        for (pair<int, int> info : graph[cur_node]) {
            int next_node = info.first;
            int dist = info.second;
            if (cur_dist + dist < d[next_node]) {
                d[next_node] = cur_dist + dist;
                pq.push({cur_dist + dist, next_node});
            }
        }
    }

    v1_dist += d[n]; // 1 ~ v1 + v1 ~ v2 + v2 ~ n

    //* 2-2. v2를 먼저 방문해서 n번 정점에 도착하는 경우
    fill(d, d+n+1, INF); d[v2] = 0;
    pq.push({0, v2});

    while (!pq.empty()) {
        int cur_dist = pq.top().first;
        int cur_node = pq.top().second;
        pq.pop();

        if (cur_dist != d[cur_node]) {
            continue;
        }

        for (pair<int, int> info : graph[cur_node]) {
            int next_node = info.first;
            int dist = info.second;
            if (cur_dist + dist < d[next_node]) {
                d[next_node] = cur_dist + dist;
                pq.push({cur_dist + dist, next_node});
            }
        }
    }

    v2_dist += d[v1]; // 1 ~ v2 + v2 ~ v1

    fill(d, d+n+1, INF); d[v1] = 0;
    pq.push({0, v1});

    while (!pq.empty()) {
        int cur_dist = pq.top().first;
        int cur_node = pq.top().second;
        pq.pop();

        if (cur_dist != d[cur_node]) {
            continue;
        }

        for (pair<int, int> info : graph[cur_node]) {
            int next_node = info.first;
            int dist = info.second;
            if (cur_dist + dist < d[next_node]) {
                d[next_node] = cur_dist + dist;
                pq.push({cur_dist + dist, next_node});
            }
        }
    }

    v2_dist += d[n]; // 1 ~ v2 + v2 ~ v1 + v1 ~ n

    //* 3. 2번 중에서 더 작은 값을 결과 값으로 출력 (둘다 INF일 경우 -1 출력)
    int result = min(v1_dist, v2_dist);

    if (result >= INF) {
        cout << -1 << '\n';
    } else {
        cout << result << '\n';
    }

    return 0;
}