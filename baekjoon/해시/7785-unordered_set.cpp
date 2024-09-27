#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    unordered_set<string> logs;
    while (n--) {
        string user, status;
        cin >> user >> status;
        if (status == "enter") {
            logs.insert(user);
        } else {
            logs.erase(user);
        }
    }

    vector<string> exist(logs.begin(), logs.end());
    sort(exist.begin(), exist.end(), greater<string>());

    for (string s : exist) {
        cout << s << '\n';
    }

    return 0;
}