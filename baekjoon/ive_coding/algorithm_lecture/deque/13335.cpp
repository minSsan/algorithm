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

    bridge.push_back(inputs[0]);
    int index = 1;
    int result = 1;
    int sum = inputs[0];

    while (!bridge.empty() && sum != 0) {
        result++;
        if (bridge.size() == w) {
            sum -= bridge.front();
            bridge.pop_front();
        }

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