#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(pair<int, string> a, pair<int, string> b) {
    return a.first > b.first;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p, price;
    string name;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> p;
        vector<pair<int, string>> list;
        for (int j = 0; j < p; ++j) {
            cin >> price >> name;
            list.push_back({price, name});
        }
        sort(list.begin(), list.end(), compare);
        cout << list[0].second << '\n';
    }

    return 0;
}