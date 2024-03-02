#include <iostream>

using namespace std;

// 1부터 n까지 자연수 중 m개를 고른 수열
// 같은 수 중복 가능
// 비내림차순 (뒤에 오는 것이 앞에 것보다 크거나 같다)

int n, m;

int result[8];

void dfs(int cnt) {
    if (cnt == m) {
        for (int i = 0; i < m; ++i) {
            cout << result[i] << ' ';
        }
        cout << '\n';
        return ;
    }
    
    
    for (int i = 1; i <= n; ++i) {
        if (cnt == 0 || i >= result[cnt - 1]) {
            result[cnt] = i;
            dfs(cnt + 1);
        }
    }
}

int main()
{
    cin >> n >> m;
    
    dfs(0);

    return 0;
}

