import java.util.*;

class Solution {
    int _answer = 0;
    int n;

    void dfs(int sum, int len, int[] numbers, int target) {
        if (len == n) {
            if (sum == target) {
                ++_answer;
            }
            return ;
        }

        dfs(sum + numbers[len], len+1, numbers, target);
        dfs(sum - numbers[len], len+1, numbers, target);
    }

    public int solution(int[] numbers, int target) {
        int answer = 0;
        n = numbers.length;
        dfs(0, 0, numbers, target);
        return _answer;
    }
}