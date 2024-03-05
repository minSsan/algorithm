#include <iostream>
#include <vector>

using namespace std;

//? 1부터 n까지의 자연수 중, 중복 없이 m개의 숫자로 구성된 수열

short n, m;
bool visited[9];
vector<short> result;

void dfs(short len) {
    if (len == m) {
        for (int i = 0; i < result.size(); ++i) {
            cout << result[i] << ' ';
        }
        cout << '\n';
        return ;
    }

    for (short i = 1; i <= n; ++i) {
        if (!visited[i] && len+1 <= m) {
            visited[i] = true;
            result.push_back(i);
            dfs(len+1);
            visited[i] = false;
            result.pop_back();
        }
    }
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> n >> m; // 4 2

    dfs(0);

    return 0;
}