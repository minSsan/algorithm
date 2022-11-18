#include <iostream>
#include <queue>

using namespace std;

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    priority_queue<int, vector<int>, greater<int>> pq; // 큰부분 -> 최소힙
    priority_queue<int> pq2; // 작은부분 -> 최대힙
    int input_num;

    for (int i = 1; i <= n; ++i) {
        cin >> input_num;
        
        if (i == 1) {
            pq2.push(input_num);
        } else if (i == 2) {
            if (pq2.top() < input_num) {
                pq.push(input_num);
            } else {
                pq.push(pq2.top());
                pq2.pop();
                pq2.push(input_num);
            }
        } else if (input_num < pq.top()) {
            pq2.push(input_num);
        }  else {
            pq.push(input_num);
        }

        if (pq2.size() < pq.size()) {
            pq2.push(pq.top());
            pq.pop();
        } else if (pq2.size() - pq.size() > 1) {
            pq.push(pq2.top());
            pq2.pop();
        }

        cout << pq2.top() << '\n';
    }

    return 0;
}
// 3
// 1 3
// 1 3 5 
// 1 2 3 5
// 1 2 3 4 5
// 1 2 3 | 4 5

// pq (최소힙)
// 5 10

// pq2 (최대힙)
// -99 1 2

// 1 1 2 2 

// n == 1: 1
// n == 2: 1 5
// n == 3: 1 2 5
// n == 4: 1 2 5 10
// n == 5: -99 1 2 5 10
// n == 6: -99 1 2 5 7 10
// n == 7: -99 1 2 5 5 7 10

// 힙의 개수가 덱의 개수보다 1 작거나 같을 때까지, 덱의 back 출력
// n = 1
// 1

// n = 2
// 1 5
// 5 -> 1

// n = 3
// 2 5 -> 1
// 5 -> 1 2

// n = 4
// 2 5 10 -> 1
// 5 10 -> 1 2

// n = 5
// -99 5 10 -> 1 2
// 5 10 -> -99 1 2

// n = 6
// 5 7 10 -> -99 1 2

// n = 7
// 5 5 7 10 -> -99 1 2
// 5 7 10 -> -99 1 2 5
