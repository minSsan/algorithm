#include <iostream>
#include <vector>

using namespace std;

int n, s;
int cnt;
vector<int> seq;

void dfs(int current_index, int sum) {
    if (sum == s) {
        cnt++;
    }

    if (current_index == n) return ;

    if (sum == s) { 
        // 원하는 합이 나왔을 경우에는, 현재 값을 무조건 더해주어야 한다. 
        dfs(current_index+1, sum+seq[current_index]); // 현재 값을 더하는 경우
    }
    else {
        dfs(current_index+1, sum); // 현재 값을 안 더하는 경우
        dfs(current_index+1, sum+seq[current_index]); // 현재 값을 더하는 경우
    }
}

int main() {
    cin >> n >> s;

    int input_num;
    for (int i = 0; i < n; ++i) {
        cin >> input_num;
        seq.push_back(input_num);
    }

    dfs(0, 0);

    cout << cnt << '\n';

    return 0;
}