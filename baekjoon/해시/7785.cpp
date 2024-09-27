#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

bool compare(pair<string, bool> a, pair<string, bool> b) {
    return a.first > b.first;
}

int main() {
    int n;
    cin >> n;

    unordered_map<string, bool> logs;
    while (n--) {
        string user, status;
        cin >> user >> status;
        if (status == "enter") {
            logs[user] = true;
        } else {
            logs[user] = false;
        }
    }

    vector<pair<string, bool>> exist;
    unordered_map<string, bool>::iterator iter = logs.begin();
    while (iter != logs.end()) {
        if (iter->second) exist.push_back(*iter);
        iter++;
    }

    sort(exist.begin(), exist.end(), compare);

    for (pair<string, bool> info : exist) {
        cout << info.first << '\n';
    }

    return 0;
}