#include <iostream>
#include <queue>

// 값을 넣을 때마다 정렬이 필요할 때 사용 가능 (ex. 점수 랭킹 -> N * logN : n명에 대해서 각 점수가 주어질 때마다 힙에다가 넣음)
// 시간 복잡도 logN (퀵정렬은 N*logN -> N * (NlogN))

using namespace std;

int main() {
    // 힙
    priority_queue<int>pq;

    // 최대값을 우선순위로
    pq.push(1);
    pq.push(3);
    pq.push(2);

    cout << pq.top(); // 3

    // 최소값을 우선순위로
    pq.push(-1);
    pq.push(-3);
    pq.push(-2);

    cout << -pq.top(); // 1

    // pq.pop();

    return 0;
}