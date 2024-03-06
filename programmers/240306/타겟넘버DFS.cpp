#include <string>
#include <vector>

using namespace std;

int answer;

void dfs(vector<int> &numbers, int &target, int cnt, int result) {
    if (cnt == numbers.size()) {
        if (result == target) ++answer;
        return ;
    }
    dfs(numbers, target, cnt+1, result + numbers[cnt]);
    dfs(numbers, target, cnt+1, result - numbers[cnt]);
}

int solution(vector<int> numbers, int target) {
    dfs(numbers, target, 0, 0);
    
    return answer;
}