#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main() {
    int n, w, l;
    cin >> n >> w >> l;

    deque<int> bridge;
    vector<int> inputs;

    int weight;
    for (int i = 0; i < n; ++i) {
        cin >> weight;
        inputs.push_back(weight);
    }

    int index = 0;
    int sum, result = 0;
    while (index < n) {
        weight = inputs[index];
        if (bridge.size() == w) {
            sum -= bridge.front();
            bridge.pop_front();
        }

        if (sum + weight <= l) {
            sum += weight;
            bridge.push_back(weight);
            ++index;
        } else {
            bridge.push_back(0);
        }

        ++result;
    }

    while (!bridge.empty()) {
        bridge.pop_front();
        result++;
    }

    cout << result << '\n';

    return 0;
}