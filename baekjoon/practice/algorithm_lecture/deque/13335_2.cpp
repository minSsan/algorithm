#include <iostream>
#include <deque>

using namespace std;

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    deque<int> bridge;
    int n, w, l;
    cin >> n >> w >> l;

    while (w--) {
        bridge.push_back(0);
    }

    int truck, sum = 0, result = 0;

    while (n--) {
        cin >> truck;
        sum -= bridge.front();
        bridge.pop_front();
        while (sum + truck > l) {
            sum -= bridge.front();
            bridge.pop_front();
            bridge.push_back(0);
            result++;
        }
        bridge.push_back(truck);
        sum += truck;
        result++;
    }

    while (!bridge.empty()) {
        result++;
        bridge.pop_front();
    }

    cout << result << '\n';

    return 0;
}