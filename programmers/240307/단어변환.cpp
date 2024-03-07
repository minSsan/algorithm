#include <string>
#include <vector>
#include <queue>

using namespace std;

// begin -> target으로 변환하되, 한 단어만 바꿀 수 있다.
// 즉, 단어 차이가 1인 곳으로만 이동할 수 있음
// 각 단어에서 다른 단어로 이동하는 경로(= 다른 알파벳 수)를 모두 구한 후 탐색

int word_len;

int get_diff(string word1, string word2) {
    int difference = 0;
    for (int k = 0; k < word_len; ++k) {
        if (word1[k] != word2[k]) ++difference;
    }
    return difference;
}

int solution(string begin, string target, vector<string> words) {
    word_len = words[0].size();
    
    int cnt[50] = {0, }; // start에서 i 번째 단어(= words[i])로 가는데 거친 단계
    queue<int> q;
    // start 와 차이가 1인 단어 찾기
    for (int i = 0; i < words.size(); ++i) {
        if (get_diff(begin, words[i]) == 1) {
            q.push(i);
            cnt[i] = 1;
        }
    }
    
    int current_index, current_cnt;
    while(!q.empty()) {
        current_index = q.front(); 
        current_cnt = cnt[current_index];
        q.pop();
        
        if (words[current_index] == target) return current_cnt;
        
        for (int i = 0; i < words.size(); ++i) {
            if (current_index == i) continue;
            if (get_diff(words[current_index], words[i]) == 1 && cnt[i] == 0) {
                q.push(i);
                cnt[i] = current_cnt+1;
            }
        }
    }
    
    return 0;
}