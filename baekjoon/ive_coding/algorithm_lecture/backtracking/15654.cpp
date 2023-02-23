#include <iostream>
#include <algorithm>

using namespace std;

int n, m;
int nums[8];
int result[8];
bool visited[10001];

void dfs(int cnt) {
    if (cnt == m) { // 크기가 m인 수열이 완성되었다면, 출력 후 종료
        for (int i = 0; i < m; ++i) {
            cout << result[i] << " ";
        }
        cout << '\n';
        return ;
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[nums[i]]) {
            result[cnt] = nums[i];
            visited[nums[i]] = true;
            dfs(cnt + 1);
            result[cnt] = 0;
            visited[nums[i]] = false;
        }
    }
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    sort(nums, nums + n);

    dfs(0);

    return 0;
}