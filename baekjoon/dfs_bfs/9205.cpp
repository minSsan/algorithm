#include <iostream>
#include <queue>
#include <vector>
#include <string>

#define MAX 1000

using namespace std;

bool visited[101]; // v의 n번째 요소 방문여부

// ? 현재 위치에서 이동할 수 있는 (distance <= 1000인 위치) 위치를 모두 q에 푸시
// ? q에서 꺼낸 요소가 도착지와 일치하면 happy 출력 후 다음 테스트 케이스
// * 방문체크 ?

pair<short, short> start, dest, current;
vector<pair<short, short>> v;

int distance(pair<short, short> a, pair<short, short> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

string bfs(pair<short, short> start) {
    queue<pair<short, short>> q;
    q.push(start);

    while (!q.empty()) {
        current = q.front(); q.pop();

        if (current.first == dest.first && current.second == dest.second) {
            return "happy\n";
        }

        for (int i = 0; i < v.size(); ++i) {
            if (!visited[i] && distance(current, v[i]) <= MAX) {
                q.push(v[i]);
                visited[i] = true;
            }
        }
    }
    return "sad\n";
}

int main() {
    short t, n, x, y;
    cin >> t;
    //? -- 입력 --
    for (int i = 0; i < t; ++i) {
        cin >> n;
        cin >> start.first >> start.second;
        for (int j = 0; j < n; ++j) {
            cin >> x >> y;
            v.push_back({x, y});
        }
        cin >> dest.first >> dest.second;
        v.push_back({dest.first, dest.second});
        //? ---------

        cout << bfs(start);

        v.clear();
        for (int k = 0; k < n+1; ++k) visited[k] = false;
    }


    return 0;
}