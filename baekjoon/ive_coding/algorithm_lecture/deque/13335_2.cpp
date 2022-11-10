#include <iostream>
#include <deque>

using namespace std;

int main() {
    deque<int> bridge;
    int n, w, l;
    cin >> n >> w >> l;

    int truck, sum, result = 0;

    while (n--) {
        cin >> truck;
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