#include <iostream>
#include <queue>

using namespace std;
int n, k;
int min_time[100001];

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> n >> k;

    int location, time;
    queue<int> q; // 위치
    q.push(n);
    while (!q.empty()) {
        location = q.front(); time = min_time[location];
        q.pop();

        if (location == k) break;
        
        if (location - 1 >= 0 && min_time[location-1] == 0) {
            min_time[location - 1] = time + 1;
            q.push(location-1);
        }

        if (location + 1 <= 100000 && min_time[location+1] == 0) {
            min_time[location + 1] = time + 1;
            q.push(location+1);
        }

        if (location * 2 <= 100000 && min_time[location*2] == 0) {
            min_time[location * 2] = time + 1;
            q.push(2*location);
        }
    }
    cout << time << '\n';

    return 0;
}