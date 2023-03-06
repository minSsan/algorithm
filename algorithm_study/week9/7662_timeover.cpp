#include <iostream>
#include <queue>
#include <deque>

using namespace std;

// * k ≤ 1,000,000
// * D 1 : 최댓값 삭제
// * D -1: 최솟값 삭제

int main() {
    int t, k;
    cin >> t;

    char command;
    int num;

    priority_queue<int> max_heap;
    priority_queue<int, vector<int>, greater<int>> min_heap;
    queue<int> q;

    int min = 2147483647, max = -2147483648;

    for (int i = 0; i < t; ++i) {
        cin >> k;
        for (int j = 0; j < k; ++j) {
            cin >> command >> num;
            switch (command) {
                case 'I':
                    q.push(num);
                    break;
                
                case 'D':
                    if (!q.empty()) {
                        if (num == -1) { // 최소값 pop
                            while (!q.empty()) {
                                min_heap.push(q.front()); // nlogn -> n^2logn (시간초과)
                                q.pop();
                            }
                            min_heap.pop();
                            while (!min_heap.empty()) {
                                q.push(min_heap.top());
                                min_heap.pop();
                            }
                        } else { // 최대값 pop
                            while (!q.empty()) {
                                max_heap.push(q.front()); // nlogn -> n^2logn (시간초과)
                                q.pop();
                            }
                            max_heap.pop();
                            while (!max_heap.empty()) {
                                q.push(max_heap.top());
                                max_heap.pop();
                            }
                        }
                    }
                    break;

                default:
                    break;
            }
        }

        if (q.empty()) {
            cout << "EMPTY\n";
        }
        else {
            while (!q.empty()) {
                if (q.front() < min) {
                    min = q.front();
                }

                if (q.front() > max) {
                    max = q.front();
                }

                q.pop();
            }
            cout << max << ' ' << min << '\n';
        }
    }
    return 0;
}