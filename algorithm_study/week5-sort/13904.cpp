#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

// * 마감일이 임박한 과제 순서대로 하나씩 확인하여 수행 가능 여부 판단 :: (d - day) >= 0이면 수행 가능한 상태
// * - 수행 가능하면 현재 과제의 w를 submit(min heap)에 push하고 day(지난 날짜)값을 1 증가시킨다.
// * - 수행 가능하지 않다면 submit 중 최솟값을 pop하고 현재 과제의 w를 push한다. (day값은 그대로)

int main() {
    int n, d, w;
    cin >> n;
    vector<pair<int,int>> assignments(n);
    for (int i = 0; i < n; ++i) {
        cin >> assignments[i].first >> assignments[i].second;
    }
    // ? 마감일이 임박한 과제 순으로 정렬한다.
    sort(assignments.begin(), assignments.end());

    int day = 0, result = 0;
    priority_queue<int, vector<int>, greater<int>> submit;
    for (int i = 0; i < n; ++i) {
        d = assignments[i].first; w = assignments[i].second;
        if (d - day > 0) { // ? 마감일이 지나지 않은 과제인 경우 -> 무조건 push
            submit.push(w); 
            result += w;
            day++;
        } else if (submit.top() < w) { // ? 마감일이 지났지만 앞서 제출한 과제중에서 w가 더 작은게 있는 경우 -> 해당 과제를 pop하고 현재 과제를 push
            result -= submit.top(); 
            result += w;
            submit.pop();
            submit.push(w);
        }
    }

    cout << result << '\n';

    return 0;
}