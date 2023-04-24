#include <string>
#include <vector>
#include <queue>

using namespace std;

// ? queue1에 있는 모든 원소의 합: sum1, queue2에 있는 모든 원소의 합: sum2

// ? sum1(14) < sum2(15) -> queue2의 top을 뽑아서 queue1에 추가
// ? sum1(18) > sum2(12) -> queue1의 top을 뽑아서 queue2에 추가
// ? sum1(15) == sum2(15)

// ? queue1 = [1, 2] | queue2 = [8, 1, 4]
// ? sum1(3) < sum2(13)
// ? sum1(11) > sum2(5) - 1
// ? sum1(10) > sum2(6) - 2
// ? sum1(8) == sum2(8) - 3

// * 원소가 0개인지 확인 필요.

int solution(vector<int> queue1, vector<int> queue2) {
    int answer = 0;
    
    int max_cnt = queue1.size() + queue2.size();
    
    queue<int> q1, q2;
    long long q1_sum = 0, q2_sum = 0;
    for (int i = 0; i < queue1.size(); ++i) {
        q1.push(queue1[i]);
        q1_sum += queue1[i];
    }
    for (int i = 0; i < queue2.size(); ++i) {
        q2.push(queue2[i]);
        q2_sum += queue2[i];
    }
    
    while (answer < max_cnt && q1_sum != q2_sum) {
        if (q1_sum > q2_sum) {
            q1_sum -= q1.front();
            q2_sum += q1.front();
            q2.push(q1.front()); q1.pop();
        } else {
            q2_sum -= q2.front();
            q1_sum += q2.front();
            q1.push(q2.front()); q2.pop();
        }
        answer++;
    }

    if (answer == max_cnt) answer = -1;
    
    return answer;
}