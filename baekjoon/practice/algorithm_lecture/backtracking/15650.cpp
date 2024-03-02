#include <iostream>

using namespace std;

int n, m;

// 1부터 n까지 자연수 중 중복 없이 m개를 고른 수열
// 수열은 오름차순

bool visited[9];
int result[9];

void dfs(int cnt) {
    // 수열의 갯수가 m개가 되면 출력 후 종료
    if (cnt == m) {
        for (int i = 0; i < m; ++i) {
            cout << result[i] << ' ';
        }
        cout << '\n';
        return ;
    }
    
    for (int i = 1; i <= n; ++i) {
        if (!visited[i] && i > result[cnt - 1]) {
            result[cnt] = i;
            visited[i] = true;
            dfs(cnt + 1);
            result[cnt] = 0;
            visited[i] = false;
        }
    }
}

int main()
{
    cin >> n >> m;
    
    dfs(0);

    return 0;
}

