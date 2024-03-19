#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

//! 그리디 - 강의 시작 시간이 앞서는 것을 우선 배정한다. (모든 강의를 효율적으로 배치해야 함)
//? 그리디 전제 검증 - 시작 시간이 앞서는 강의를 먼저 넣는 것이 최소 강의실 수를 만족할 수 있는가?
//?     -> 종료 시간'도' 더 빠른 것으로 넣는게 유리하다. (뒤에 들어오는 강의를 충분히 넣을 수 있는 가능성이 높아지기 때문)
//?         -> 각 강의실의 시간표를 확인하고, 가장 마지막 강의의 종료 시간이 현재 강의 시간보다 늦으면 현재 강의로 바꾼다. 
//?         -> 강의가 바뀌었다면 s와 t를 바뀐 시간으로 변경하여 탐색

// 1 3
// 2 5
// 3 7
// 4 6
// 6 7

// 5, 6, 7

// 1 - 3, 4 - 6 | 2 - 5 | 3 - 7
// 3
// {1, 3}, {2, 5}
// {3, 7}, {2, 5}
// {4, 6}, {2, 5}, {3, 7}
// {6, 7}, {2, 5}, {3, 7}

bool comp(pair<int, int> a, pair<int, int> b) {
    return a.second < b.second;
}

int main() {
    int n, s, t;
    cin >> n;

    vector<pair<int, int>> v;
    for (int i = 0; i < n; ++i) {
        cin >> s >> t;
        v.push_back({s, t});
    }

    sort(v.begin(), v.end()); // 종료시간 기준 오름차순 정렬

    priority_queue<int, vector<int>, greater<int>> pq; // 종료시간이 앞서는 강의실 순서로 저장

    for (int i = 0; i < n; ++i) {
        pq.push(v[i].second); 
        if (pq.top() <= v[i].first) { // 가장 빨리 끝나는 강의시간에 이어서 배정받을 수 있는 경우
            pq.pop(); // 강의를 이어서 진행하므로 강의 종료 시간을 현재 강의 종료시간으로 갱신
        }
    }

    cout << pq.size() << '\n';

    return 0;
}