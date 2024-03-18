#include <string>
#include <vector>
#include <queue>

using namespace std;

// 모든 음식의 스코빌 지수가 K 이상이 될 때까지 반복해서 섞는다.
// 섞은 스코빌 = 가장 낮은 스코빌 + (두 번째로 낮은 스코빌 * 2)

int solution(vector<int> scoville, int K) {
    int answer = 0; // 스코빌이 K 이상이 되기 위해 섞어야 하는 최소 횟수
    // 모든 음식의 스코빌 지수를 K 이상으로 만들 수 없는 경우 -1
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    
    // init pq
    for (int i = 0; i < scoville.size(); ++i) {
        pq.push(scoville[i]);
    }
    
    long long first, second; // 첫 번째로 낮은, 두 번째로 낮은
    // 반복
    while (pq.size() > 1) {
        // 최솟값이 K 이상 -> 모든 음식이 K 이상
        if (pq.top() >= K) {
            break;
        }
        first = pq.top(); pq.pop();
        second = pq.top(); pq.pop();
        pq.push(first+second*2);
        ++answer;
    }
    
    if (pq.size() == 1 && pq.top() < K) answer = -1;
    
    return answer;
}