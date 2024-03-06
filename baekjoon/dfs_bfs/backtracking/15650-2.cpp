#include <iostream>
#include <vector>

using namespace std;

//? 1 ~ n까지의 중복되지 않는 숫자로 구성된 길이가 m인 수열
//? 수열은 오름차순

int n, m;
bool visited[9];
vector<int> v;

// 길이 기준
void dfs(int len) {
    if (len == m) {
        for (int i = 0; i < m; ++i) {
            cout << v[i] << ' ';
        }
        cout << '\n';
        return ;
    }

    for (int i = 1; i <= n; ++i) {
        if (len == 0 || !visited[i] && i > v[len-1]) {
            visited[i] = true;
            v.push_back(i);
            dfs(len+1);
            v.pop_back();
            visited[i] = false;
        }
    }
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;

    // 길이 기준
    dfs(0);

    return 0;
}