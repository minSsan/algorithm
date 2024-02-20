#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

// 가장 나이가 적은 사람의 이름
// 가장 나이가 많은 사람의 이름 출력

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, year, month, day;
    cin >> n;
    string name;
    vector<tuple<int, int, int, string>> list;

    for (int i = 0; i < n; ++i) {
        cin >> name >> day >> month >> year;
        list.push_back(make_tuple(year, month, day, name));
    }

    sort(list.begin(), list.end()); // year, month, day 기준 오름차순 정렬 -> 나이가 많은 순으로 정렬

    cout << get<3>(list[list.size() - 1]) << '\n';
    cout << get<3>(list[0]) << '\n';

    return 0;
}