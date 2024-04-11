import java.util.*;

// 현재 단어와 비교(compareTo)해서 그 결과의 절댓값이 1이면 q에 푸시한다.
// 각 단어까지 도달하는 데 거친 과정 수를 기록한다.

class Solution {
    Queue<Integer> q = new LinkedList<>();
    int[] cnt;

    public boolean isOneInterval(String a, String b) {
        int cnt = 0;
        for (int i = 0; i < a.length(); ++i) {
            if (a.charAt(i) != b.charAt(i)) ++cnt;
        }
        return cnt == 1;
    }

    public int solution(String begin, String target, String[] words) {
        cnt = new int[words.length];
        // 0. 첫 시작 단어 찾기
        for (int i = 0; i < words.length; ++i) {
            if (isOneInterval(begin, words[i])) {
                cnt[i] = 1;
                q.add(i);
            }
        }
        // 1. bfs 탐색
        while (!q.isEmpty()) {
            int current_index = q.peek();
            String word = words[current_index];
            q.remove();

            if (word.equals(target)) {
                return cnt[current_index];
            }

            for (int i = 0; i < words.length; ++i) {
                if (cnt[i] == 0 && isOneInterval(word, words[i])) {
                    cnt[i] = cnt[current_index]+1;
                    q.add(i);
                }
            }
        }

        return 0;
    }
}