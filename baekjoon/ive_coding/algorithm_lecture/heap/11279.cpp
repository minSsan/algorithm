#include <iostream>
#include <queue>

using namespace std;

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    priority_queue<int> pq;
    int n;
    cin >> n;

    int input_num;
    for (int i = 0; i < n; ++i) {
        cin >> input_num;
        if (input_num == 0) {
            if (!pq.empty()) {
                cout << pq.top();
                pq.pop();
            } else {
                cout << '0';
            }
            cout << '\n';
        } else {
            pq.push(input_num);
        }
    }

    return 0;
}