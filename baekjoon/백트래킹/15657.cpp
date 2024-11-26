#include <iostream>
#include <vector>
#include <algorithm>

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

    for (int i = 0; i < n; ++i) {
        if (v.empty() || nums[i] >= v.back()) {
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