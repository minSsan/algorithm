#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
int nums[10];
vector<int> v;
bool visited[10];

void dfs() {
    if (v.size() == m) {
        for (int number : v) {
            cout << number << ' ';
        }
        cout << '\n';
        return;
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i] && (v.empty() || nums[i] >= v.back())) {
            visited[i] = true;
            v.push_back(nums[i]);
            dfs();
            visited[i] = false;
            v.pop_back();
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