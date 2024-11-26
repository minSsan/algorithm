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
        if (!visited[i] && nums[i] != last) {
            //* 가지가 분기되는 지점에서, 새로 뻗어지는 가지 값을 저장
            //?     오름차순 정렬되어 있기 때문에, 같은 숫자는 인접 -> last 값이 같으면 동일 base의 직전 분기에서 이미 처리했음을 알 수 있음
            last = nums[i];
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