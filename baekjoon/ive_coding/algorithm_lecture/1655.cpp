#include <iostream>
#include <queue>

using namespace std;

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    priority_queue<int, vector<int>, greater<int>> pq_bigger; // 큰부분 -> 최소힙
    priority_queue<int> pq_smaller; // 작은부분 -> 최대힙
    int input_num;

    for (int i = 1; i <= n; ++i) {
        cin >> input_num;
        
        // * 초기 값 세팅 :: pq_bigger, pq_smaller 결정하기
        // ? pq_bigger, pq_smaller 내부 요소 집합은 요소가 2개 이상일 때부터 결정 가능
        if (i == 1) {
            pq_smaller.push(input_num);
        } else if (i == 2) {
            if (pq_smaller.top() < input_num) {
                pq_bigger.push(input_num);
            } else {
                pq_bigger.push(pq_smaller.top());
                pq_smaller.pop();
                pq_smaller.push(input_num);
            }
        } 
        // * pq_bigger과 pq_smaller가 결정된 상태일 때 - 입력받은 숫자를 적절한 위치에 push
        else if (input_num < pq_bigger.top()) {
            pq_smaller.push(input_num);
        }  else {
            pq_bigger.push(input_num);
        }

        // * 가운데 위치한 숫자 찾기
        if (pq_smaller.size() < pq_bigger.size()) {
            pq_smaller.push(pq_bigger.top());
            pq_bigger.pop();
        } else if (pq_smaller.size() - pq_bigger.size() > 1) {
            pq_bigger.push(pq_smaller.top());
            pq_smaller.pop();
        }

        cout << pq_smaller.top() << '\n';
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

// pq_smaller (최대힙)
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
