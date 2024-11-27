#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, m;
int nums[10];
bool visited[10];
vector<int> v;

void dfs() {
    if (v.size() == m) {
        for (int num : v) {
            cout << num << ' ';
        }
        cout << '\n';
        return ;
    }

    int last = -1;
    for (int i = 0; i < n; ++i) {
        if (!visited[i] && (nums[i] != last && (v.empty() || nums[i] >= v.back()))) {
            visited[i] = true;
            v.push_back(nums[i]);
            last = nums[i];
            dfs();
            v.pop_back();
            visited[i] = false;
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    sort(nums, nums + n);

    dfs();

    return 0;
}