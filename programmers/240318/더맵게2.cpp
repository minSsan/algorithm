#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> scoville, int K) {
    int answer = 0;
    priority_queue<int, vector<int>, greater<int>> pq(scoville.begin(), scoville.end()); // 최소힙
    
    int first, second;
    while(pq.top() < K) {
        if (pq.size() == 1) return -1;
        first = pq.top(); pq.pop();
        second = pq.top(); pq.pop();
        pq.push(first+second*2);
        ++answer;
    }
    
    return answer;
}