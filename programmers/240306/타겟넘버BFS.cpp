#include <string>
#include <vector>
#include <queue>

// 시도 횟수가 numbers.size() 보다 작고, 더하거나 뺀 값이 범위 내에 포함되면 push
// 만약 시도 횟수가 numbers.size()와 일치하고, 더한 값이 target과 일치하면 answer++

using namespace std;

int solution(vector<int> numbers, int target) {
    int answer = 0;
    
    int current_value, current_try;
    queue<pair<int, int>> q; // 더한 결과, 시도 횟수
    q.push({0, 0});
    
    while(!q.empty()) {
        current_value = q.front().first; current_try = q.front().second;
        q.pop();
        
        if (current_try == numbers.size()) {
            if (current_value == target) ++answer;
            continue;
        }
        
        if (current_try + 1 <= numbers.size()) {
            // 더한 결과
            q.push({current_value+numbers[current_try], current_try+1});
            // 뺀 결과
            q.push({current_value-numbers[current_try], current_try+1});
        }
    }
    
    return answer;
}