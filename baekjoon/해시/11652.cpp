#include <iostream>
#include <map>

using namespace std;

int main() {
    int n;
    cin >> n;

    map<long long, int> note;

    for (int i = 0; i < n; ++i) {
        long long v;
        cin >> v;
        if (note.find(v) == note.end()) {
            note[v] = 1;
        } else {
            note[v]++;
        }
    }

    map<long long, int>::iterator iter = note.begin();
    int max_cnt = 0;
    long long max_v = -(2 << 62)-1;
    while (iter != note.end()) {
        if (iter->second > max_cnt) {
            max_v = iter->first;
            max_cnt = iter->second;
        }
        iter++;
    }

    cout << max_v << '\n';

    return 0;
}