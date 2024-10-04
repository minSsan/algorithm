#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 100005;

struct road {
    int dest; // 목적지 마을 번호
    int time; // dest까지 가는데 걸리는 시간
};

int main() {
    int n, m, x;
    cin >> n >> m >> x;

    vector<road> graph[n+1];
    for (int i = 0; i < m; ++i) {
        int s, e, t;
        cin >> s >> e >> t;
        graph[s].push_back({e, t});
    }

    int d_dest[n+1]; // i에서 x번 마을까지 가는 최단경로
    int d_town[n+1]; // x번 마을에서 i까지 가는 최단경로
    fill(d_dest, d_dest+n+1, INF);
    fill(d_town, d_town+n+1, INF);

    //* 1. x번 마을에서 모든 마을로 가는 최단경로 기록 (d_town)
    // { 시간, 마을 번호 }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, x});
    d_town[x] = 0;

    while (!pq.empty()) {
        pair<int, int> cur = pq.top();
        pq.pop();
        int cur_node = cur.second, cur_time = cur.first;
        // 더 빠른 최단경로에 의해 업데이트 된 경우 처리
        if (d_town[cur_node] != cur_time) continue;
        
        for (road coord : graph[cur_node]) {
            if (cur_time + coord.time < d_town[coord.dest]) {
                d_town[coord.dest] = cur_time + coord.time;
                pq.push({d_town[coord.dest], coord.dest});
            }
        }
    }

    // for (int i = 1; i <= n; ++i) {
    //     cout << i << "번 마을의 돌아오는 시간: " << d_town[i] << '\n';
    // }

    //* 2. 모든 마을에 대해서 x번 마을로 가는 최단경로 기록 (d_dest)
    for (int start = 1; start <= n; ++start) {
        int d[n+1]; // start에서 각 마을까지의 최단거리
        fill(d, d+n+1, INF);
        d[start] = 0;

        pq.push({0, start});

        while (!pq.empty()) {
            pair<int, int> cur = pq.top();
            pq.pop();
            int cur_node = cur.second, cur_time = cur.first;

            if (cur_time != d[cur_node]) continue;

            for (road coord : graph[cur_node]) {
                if (cur_time + coord.time < d[coord.dest]) {
                    d[coord.dest] = cur_time + coord.time;
                    pq.push({d[coord.dest], coord.dest});
                }
            }
        }

        d_dest[start] = d[x]; // start에서 x번 마을까지의 최단거리 저장
    }

    // for (int i = 1; i <= n; ++i) {
    //     cout << i << "번 마을의 가는 시간: " << d_dest[i] << '\n';
    // }

    //* 3. d_dest 값과 d_town 값을 합친 값 구하기
    int total_time[n+1]; // i번 마을의 왕복 시간
    fill(total_time, total_time+n+1, 0);
    for (int i = 1; i <= n; ++i) {
        total_time[i] += (d_dest[i] + d_town[i]);
    }

    sort(total_time, total_time+n+1, greater<int>());

    cout << total_time[0] << '\n';

    return 0;
}