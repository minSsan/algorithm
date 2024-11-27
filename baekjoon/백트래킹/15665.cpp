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

    int last = -1; // 현재 가지에서 가장 마지막에 추가된 자식 가지
    for (int i = 0; i < n; ++i) {
        if (nums[i] != last) {
            v.push_back(nums[i]);
            last = nums[i];
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