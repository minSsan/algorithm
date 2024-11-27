#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, m;
int nums[10];
vector<int> v;

void dfs() {
    if (v.size() == m) {
        for (int num : v) {
            cout << num << ' ';
        }
        cout << '\n';
        return ;
    }

    int last = -1; // 현재 가지에서부터 가장 최근에 뻗어져 나간 가지
    for (int i = 0; i < n; ++i) {
        if (nums[i] != last && (v.empty() || nums[i] >= v.back())) {
            last = nums[i];
            v.push_back(nums[i]);
            dfs();
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