#include <iostream>
#include <queue>

using namespace std;

// * < 이중 우선순위 큐 >
// * 기본적인 동작은 힙(push -> logN)과 동일. 하지만 pop을 할 때 최대 / 최소를 각각 뽑아낼 수 있어야 함.
// * k ≤ 1,000,000
// * D 1 : 최댓값 삭제
// * D -1: 최솟값 삭제

// ? 1. 최소힙, 최대힙을 따로 사용
// ?    -> 최솟값을 뽑을 때는 최소힙에서, 최댓값을 뽑을 때는 최대힙에서.. 
// !    -> 각 힙에 들어있는 값이 서로 달라짐(최소힙에서는 없어졌는데 최대힙에서는 안 없어지는 등..) (X)
// ? -> 두 자료구조를 사용한다면, 항상 똑같은 값들을 저장하고 있어야 한다.

// ? 2. 최소힙, 최대힙을 따로 사용하되 특정 값을 기준으로 둘(작은 값들을 저장하는 힙, 큰 값들을 저장하는 힙)로 쪼개기
// !    -> 특정 값을 기준으로 둘로 쪼갤 수 없음. (중간 값이 필요한데 이를 알 수 없음.)

// ? 3. 

bool outputs[1000000]; // ? n번째로 insert된 값이 삭제되었는가?

int main() {
    int t, k;
    cin >> t;

    char command;
    int num;

    priority_queue<pair<int, int>> max_heap;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;
    int insertNum = 0; // insert된 순서
    int result_max, result_min;

    for (int i = 0; i < t; ++i) {
        cin >> k;
        for (int j = 0; j < k; ++j) {
            cin >> command >> num;
            switch (command) {
                case 'I':
                    max_heap.push({num, insertNum});
                    min_heap.push({num, insertNum});
                    insertNum++;
                    break;
                
                case 'D':
                    switch (num) {
                        case 1: // 최댓값을 뽑는 경우
                            while (!max_heap.empty() && outputs[max_heap.top().second]) {
                                max_heap.pop();
                            }

                            if (max_heap.empty()) { // 힙이 비어서 루프를 빠져나온 경우 -> 뽑을 숫자가 없음
                                break;
                            }

                            // cout << "pop: " << max_heap.top().first << '\n';
                            outputs[max_heap.top().second] = true;
                            max_heap.pop();
                            break;

                        case -1: // 최솟값을 뽑는 경우
                            while (!min_heap.empty() && outputs[min_heap.top().second]) {
                                min_heap.pop();
                            }

                            if (min_heap.empty()) { // 힙이 비어서 루프를 빠져나온 경우 -> 뽑을 숫자가 없음
                                break;
                            }

                            // cout << "pop: " << min_heap.top().first << '\n';
                            outputs[min_heap.top().second] = true;
                            min_heap.pop();
                            
                            break;
                        
                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
        }

        // * 정답 출력
        while (!max_heap.empty() && outputs[max_heap.top().second]) {
            max_heap.pop();
        }
        
        if (!max_heap.empty()) {
            result_max = max_heap.top().first;
        
            while (!min_heap.empty() && outputs[min_heap.top().second]) {
                min_heap.pop();
            }

            if (min_heap.empty()) {
                result_min = result_max;
            } else {
                result_min = min_heap.top().first;
            }

            cout << result_max << ' ' << result_min << '\n';
        } else {
            cout << "EMPTY\n";
        }


        // * -------

        // * 다음 작업을 위한 변수 초기화
        // 삭제 여부 리스트 초기화
        for (int j = 0; j < k; ++j) {
            outputs[j] = false;
        }

        while (!max_heap.empty()) {
            max_heap.pop();
        }

        while (!min_heap.empty()) {
            min_heap.pop();
        }

        insertNum = 0;
        // * ---------------------
    }

    return 0;
}