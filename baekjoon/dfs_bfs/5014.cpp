#include <iostream>
#include <queue>

using namespace std;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);


    int f, s, g, u, d;
    cin >> f >> s >> g >> u >> d; // s 층에서 g 층으로 이동하기 위한 최단거리, 건물은 1층부터 f층까지 존재
    
    int min_cnt[f+1];
    for (int i = 0; i < f+1; ++i) min_cnt[i] = -1;
    min_cnt[s] = 0;

    int current, current_cnt;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        current = q.front(); current_cnt = min_cnt[current];
        q.pop();

        if (current == g) break ;

        if (u != 0 && current + u <= f && min_cnt[current + u] == -1) {
            min_cnt[current + u] = current_cnt + 1;
            q.push(current + u);
        }

        if (d != 0 && current - d >= 1 && min_cnt[current - d] == -1) {
            min_cnt[current - d] = current_cnt + 1;
            q.push(current - d);
        }
    }
    
    if (min_cnt[g] != -1) cout << min_cnt[g] << '\n';
    else cout << "use the stairs\n";

    return 0;
}