#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

struct diamond {
    int weight;
    int value;
};

bool compare(diamond a, diamond b) {
    if (a.value != b.value) return a.value > b.value;
    return a.weight < b.weight;
}

int main() {
    int n, k;
    cin >> n >> k;
    diamond arr[n];
    for (int i = 0; i < n; ++i) {
        int m, v;
        cin >> m >> v;
        arr[i] = {m, v};
    }
    multiset<int> bags;
    for (int i = 0; i < k; ++i) {
        int c;
        cin >> c;
        bags.insert(c);
    }

    sort(arr, arr+n, compare);

    long long result = 0;
    for (diamond d : arr) {
        auto iter = bags.lower_bound(d.weight);
        if (iter != bags.end()) {
            result += d.value;
            bags.erase(iter);
        }
    }

    cout << result << '\n';

    return 0;
}