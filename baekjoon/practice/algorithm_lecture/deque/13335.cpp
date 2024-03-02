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

    for (int i = 0; i < w - 1; ++i) {
        bridge.push_back(0);
    }

    bridge.push_back(inputs[0]);
    int result = 1, index = 1, sum = inputs[0];

    while (sum != 0) {
        result++;
        sum -= bridge.front();
        bridge.pop_front();

        if (index < n && sum + inputs[index] <= l) {
            bridge.push_back(inputs[index]);
            sum += inputs[index];
            index++;
        } else {
            bridge.push_back(0);
        }
    }

    cout << result << '\n';

    return 0;
}