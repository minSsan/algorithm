#include <iostream>
#include <queue>

using namespace std;

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    
    int n;
    cin >> n;

    int start, end, cnt = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> lectures;
    priority_queue<int, vector<int>, greater<int>> end_times;
    
    for (int i = 0; i < n; ++i) {
        cin >> start >> end;
        lectures.push({start, end});
    }

    end_times.push(lectures.top().second);
    lectures.pop();
    cnt++;
    for (int i = 1; i < n; ++i) {
        start = lectures.top().first;
        end = lectures.top().second;

        if (start >= end_times.top()) {
            end_times.pop();
            end_times.push(end);
        } else {
            end_times.push(end);
            cnt++;
        }
        lectures.pop();
    }

    cout << cnt << '\n';
}