#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// * 가장 늦게 끝내도 되는 작업을 맨 뒤로 미룬다 -> 첫 작업을 늦게 시작할 수 있다.
// 5 20 -> 늦어도 15시 부터는 작업을 시작해야 한다. :: 20 - 5 == 15시에 시작
// 1 16 -> 늦어도 15시 부터는 작업을 시작해야 한다. :: min(15 - 1, 15) == 14시에 시작
// 8 14 -> 늦어도 6시 부터는 작업을 시작해야 한다. :: min(14 - 8, 6) == 6시에 시작
// 4 5 -> 늦어도 1시 부터는 작업을 시작해야 한다. :: min(6 - 4, 1) == 1시에 시작
// 3 5 -> 늦어도 2시 부터는 작업을 시작해야 한다. :: min(1 - 3, 2) = -1 불가능

// 5 20 -> {20, 5} :: time = 15
// 1 16 -> {16, 1} :: time = min(15 - 1, 15) = 14
// 8 14 -> {14, 8} :: time = min(14 - 8, 6) = 6
// 3 5 -> {5, 3} :: time = min(6 - 3, 2) = 2

// 5 20 -> 
// 1 16 -> 
// 8 14 -> 
// 4 5 -> 
// 3 5 -> 

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> works(n);

    for (int i = 0; i < n; ++i) {
        // {마감 시간, 걸리는 시간} 순으로 저장 (마감 시간이 늦은 걸 먼저 배치할 것이기 때문)
        cin >> works[i].second >> works[i].first;
    }

    sort(works.begin(), works.end()); // 오름차순 정렬
    reverse(works.begin(), works.end()); // 오름차순의 역순은 내림차순

    int time = works[0].first - works[0].second;
    for (int i = 1; i < n; ++i) {
        time = min(time - works[i].second, works[i].first - works[i].second);
        if (time < 0) {
            cout << -1 << '\n';
            return 0;
        }
    }

    cout << time << '\n';

    return 0;
}