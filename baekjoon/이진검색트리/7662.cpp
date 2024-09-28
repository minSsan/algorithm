#include <iostream>
#include <set>

using namespace std;

multiset<int> dq;
void print_dq() {
    cout << "[dq]\n";
    for (auto iter = dq.begin(); iter != dq.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << '\n';
}

const int MIN_INIT = (1 << 31) - 1;
const int MAX_INIT = -(1 << 31);

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    int t, k, n;
    char op;
    cin >> t;

    while (t--) {
        dq.clear();
        int min_value = (1 << 31) - 1;
        int max_value = -(1 << 31);
        cin >> k;
        for (int i = 0; i < k; ++i) {
            cin >> op >> n;
            // cout << "[ " << i+1 << " 번째 연산 ]\n" << "min: " << min_value << ", max: " << max_value << '\n';
            switch (op) {
            case 'D':
                if (dq.empty()) break;

                if (n == -1) {
                    //* 최솟값 삭제
                    auto iter = dq.erase(dq.find(min_value));
                    if (iter != dq.end()) {
                        if (*iter != min_value) min_value = *iter;
                    } else if (!dq.empty()) {
                        min_value = *prev(iter);
                    }
                } else {
                    //* 최댓값 삭제                    
                    auto iter = dq.erase(dq.find(max_value));

                    if (iter != dq.end()) {
                        if (*iter != max_value) max_value = *iter;
                    } else if (!dq.empty()) {
                        max_value = *prev(iter);
                    }
                }

                if (dq.empty()) {
                    min_value = MIN_INIT;
                    max_value = MAX_INIT;
                }
                break;
            case 'I':
                dq.insert(n);
                if (n < min_value) min_value = n;
                if (n > max_value) max_value = n;
                break;
            default:
                break;
            }
            // print_dq();
        }

        if (dq.empty()) {
            cout << "EMPTY\n";
        } else {
            cout << max_value << ' ' << min_value << '\n';
        }
    }

    return 0;
}