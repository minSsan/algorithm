#include <iostream>
#include <queue>
#include <deque>
#include <vector>

using namespace std;

queue<deque<int>> q;

bool visited[100001];
const int MAX = 100000;

deque<int> bfs(int start, int end) {
    visited[start] = true;
    deque<int> route;
    route.push_back(start);
    q.push(route);

    while (!q.empty()) {
        route = q.front();
        int now = route.back();
        q.pop();

        if (now == end) {
            return route;
        }

        if (now + 1 <= MAX && !visited[now + 1]) {
            visited[now + 1] = true;
            route.push_back(now + 1);
            q.push(route);
            route.pop_back();
        }

        if (now - 1 >= 0 && !visited[now - 1]) {
            visited[now - 1] = true;
            route.push_back(now - 1);
            q.push(route);
            route.pop_back();
        }

        if (2 * now <= MAX && !visited[2 * now]) {
            visited[2 * now] = true;
            route.push_back(2 * now);
            q.push(route);
            route.pop_back();
        }
    }
}

int main() {
    int n, k;
    cin >> n >> k;

    deque<int> result;

    result = bfs(n, k);

    cout << result.size() - 1 << '\n';

    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << ' ';
    }

    cout << '\n';
    
    return 0;
}