# 다익스트라 O(ElogE)

모든 정점 간 최단거리를 구하는 플로이드와 달리, 다익스트라는 **`한 정점`에서 다른 모든 정점 간 최단거리**를 구하는 알고리즘이다.

> 현재 노드와 인접한 노드 중에서 가장 거리가 가까운 노드를 방문하며, `(현재 노드까지의 거리) + (현재 노드 ~ 인접 노드까지의 거리) < 저장된 인접 노드까지의 거리`일 경우, 인접 노드의 최단거리를 갱신한다.
>
> ⭐️ 음수 간선이 없는 경우에만 유효하다. _(음수 간선이 존재하게 되면, 현재 노드로부터 가장 가까운 노드를 방문하는 것이 최단경로라는 것을 보장할 수 없기 때문)_

### 설계

- 그리디
- 우선순위 큐

**_시작 지점부터 다른 지점까지의 최단거리_** 를 구하는 알고리즘이기 때문에, 시작 지점부터 인접한 노드의 최단거리 값을 갱신하고, 그 중 가장 가까운 노드를 방문하는 순서로 동작한다.

가장 가까운 노드를 방문하기 위해 `우선순위 큐`를 이용한다.

#### 주의점

```
다른 노드에 의해 큐에 있던 노드의 최단경로가 변경될 수 있다.
⭐️ 따라서 "현재 저장된 최단경로"가 "큐에 저장된 최단경로"와 같은 값인지 확인해야 한다.
```

### 경로 복원

**각 노드의 최단경로를 갱신하는 시점**에서는 `자신의 바로 이전 방문 노드`를 알 수 있다.  
즉, **_현재 노드의 최단경로가 결정되는 시점_** 에서 바로 직전에 방문해야 하는 노드 번호를 알 수 있다.

- 시작 정점에서부터 각 정점까지의 최단 경로를 알아내기 위해, 직전 방문 노드를 기록하는 `pre 배열`을 활용할 수 있다.

```
pre[v] - 시작 정점부터 v 정점까지 최단경로로 도달하기 위해, 정점 v의 바로 직전에 방문해야 하는 노드
```

### 예제 코드

```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 20000;

int main() {
    int v, e; // 정점, 간선
    cin >> v >> e;

    int d[v+1]; // 1번 정점 ~ i번 정점까지의 거리
    fill(d, d+v+1, INF);
    d[1] = 0;

    int pre[v+1]; // i번 정점까지의 최단경로를 위해 직전에 방문한 노드
    fill(pre, pre+v+1, INF);
    pre[1] = 0;

    vector<pair<int, int>> graph[v+1]; // 노드 번호, 가중치
    for (int i = 0; i < e; ++ i) {
        int s, e, w;
        cin >> s >> e >> w;
        graph[s].push_back({e, w});
    }

    priority_queue<pair<int ,int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // 최소힙 {가중치, 노드 번호}

    pq.push({0, 1}); // 1번 노드부터 방문
    while (!pq.empty()) {
        pair<int, int> info = pq.top();
        pq.pop();

        int cur_w = info.first, cur_node = info.second;
        // ⭐️ 더 가까운 노드에 의해 최단경로 값이 이미 업데이트 된 경우
        if (d[cur_node] != cur_w) continue;

        for (pair<int, int> coord : graph[cur_node]) {
            int coord_w = coord.second, coord_node = coord.first;
            if (cur_w + coord_w < d[coord_node]) {
                d[coord_node] = cur_w + coord_w;
                pq.push({d[coord_node], coord_node});
                pre[coord_node] = cur_node;
            }
        }
    }

    // 1번 정점부터 각 정점까지의 최단경로 가중치 출력
    for (int i = 1; i <= v; ++i) {
        if (d[i] == INF) cout << "INF\n";
        else cout << d[i] << '\n';
    }

    // 각 정점까지의 최단경로 출력
    for (int dest = 1; dest <= v; ++dest) {
        cout << "1에서 " << dest << " 까지의 최단경로\n";
        if (pre[dest] == INF) {
            cout << "INF\n";
            continue;
        }

        vector<int> path;
        int cur = dest;
        while (cur != 0) {
            path.push_back(cur);
            cur = pre[cur];
        }

        reverse(path.begin(), path.end());

        for (int p : path) {
            cout << p << ' ';
        }
        cout << '\n';
    }

    return 0;
}
```
