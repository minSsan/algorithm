#include <iostream>

using namespace std;

int n;
int durability[10];
int weight[10];
int max_cnt;

void dfs(int hold, int cnt) {
    // cout << "hold: " << hold << ", cnt: " << cnt << '\n';
    if (cnt > max_cnt) max_cnt = cnt;

    if (hold >= n) {
        return ;
    }

    if (durability[hold] <= 0) {
        return dfs(hold+1, cnt);
    }

    for (int i = 0; i < n; ++i) {
        if (i != hold && durability[i] > 0) {
            durability[hold] -= weight[i];
            durability[i] -= weight[hold];
            int updated_cnt = cnt;
            if (durability[hold] <= 0) updated_cnt++;
            if (durability[i] <= 0) updated_cnt++;
            dfs(hold+1, updated_cnt);
            durability[hold] += weight[i];
            durability[i] += weight[hold];
        } 
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> durability[i] >> weight[i];
    }

    dfs(0, 0);

    cout << max_cnt << '\n';

    return 0;
}