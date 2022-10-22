#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector <int> v;

    for (int i = 1; i <= N; ++i) {
        v.push_back(i);
    }

    // while (v.size() > 1) {
    //     for (int i = 0; i < v.size(); ++i) {
    //         v.erase(v.begin() + i);
    //     }
    // }

    // 뒤부터 삭제

    // if (v.size() % 2 == 1) { // 홀수일 때
    //     index = v.size() - 1;
    // } else { // 짝수일 때
    //     index = v.size() - 2;
    // }
    
    int index;

    while (v.size() > 1) {
        if (v.size() % 2 == 1) { // 홀수일 때
            index = v.size() - 1;
        } else { // 짝수일 때
            index = v.size() - 2;
        }

        while (index >= 0) {
            v.erase(v.begin() + index);
            index = index - 2;
        }
    }

    // 1 2 3 4 5 6 7 index = 6
    // 1 2 3 4 5 6 index = 4
    // 1 2 3 4 6 index = 2
    // 1 2 4 6 index = 0

    // 1 2 4 6 index = 2
    // 1 2 6 index = 0



    cout << v.back() << '\n';

    return 0;
}