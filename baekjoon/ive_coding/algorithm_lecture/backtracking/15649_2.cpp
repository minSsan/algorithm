#include <iostream>

using namespace std;

int n, m;
bool visited[9];
int result[9];

void dfs(int cnt) {
    if (cnt == m) {
        for (int i = 0; i < m; ++i) {
            cout << result[i] << ' ';
        }
        cout << '\n';
        return ;
    }

    for (int i = 1; i <= n; ++i) {
        // 수열에 아직 i가 포함되지 않은 상태라면,
        if (!visited[i]) {
            visited[i] = true;
            result[cnt] = i;
            dfs(cnt + 1);
            visited[i] = false;
            result[cnt] = 0;
        }
    }
}

int main() {
    cin >> n >> m;

    dfs(0);

    return 0;
}