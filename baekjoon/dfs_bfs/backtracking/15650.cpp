#include <iostream>
#include <vector>

using namespace std;

//? 1 ~ n까지의 중복되지 않는 숫자로 구성된 길이가 m인 수열
//? 수열은 오름차순

int n, m;
bool visited[9];
vector<int> v;

// 숫자 기준
void dfs(int num) {
    v.push_back(num);
    if (v.size() == m) {
        for (int i = 0; i < v.size(); ++i) {
            cout << v[i] << ' ';
        }
        cout << '\n';
        return ;
    }

    for (int i = 1; i <= n; ++i) {
        if (!visited[i] && num < i) {
            visited[i] = true;
            dfs(i);
            visited[i] = false;
            v.pop_back();
        }
    }
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;

    // 시작하는 숫자 기준
    for (int i = 1; i <= n; ++i) {
        visited[i] = true;
        dfs(i); // i로 시작하는 수열 구하기
        v.clear();
    }

    return 0;
}