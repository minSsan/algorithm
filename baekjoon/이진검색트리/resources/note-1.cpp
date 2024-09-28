#include <iostream>
#include <set>

using namespace std;

multiset<int> tmp;

void print_tmp() {
    for (auto iter = tmp.begin(); iter != tmp.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << '\n';
}

int main() {
    tmp.insert(3);
    tmp.insert(3);
    tmp.insert(3);
    tmp.insert(3);
    tmp.insert(1);
    tmp.insert(5);
    tmp.insert(5);
    tmp.insert(2);
    tmp.insert(4);

    print_tmp(); // 1, 2, 3, 3, 3, 3, 4, 5, 5

    cout << distance(tmp.begin(), tmp.lower_bound(3)) << '\n'; // 2 (3이 처음 등장한 위치 - 시작 위치)

    auto range = tmp.equal_range(3);
    cout << distance(range.first, range.second) << '\n'; // 4

    tmp.erase(3);
    print_tmp(); // 1, 2, 4, 5, 5

    tmp.erase(tmp.find(5));
    print_tmp(); // 1, 2, 4, 5

    return 0;
}