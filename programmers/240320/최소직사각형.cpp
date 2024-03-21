#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//? 모든 카드를 동일한 방향으로 놓으면 최소 크기로 만들 수 있다.
//?     -> 동일한 방향으로 놓는다? = 더 긴 부위를 가로로 놓는다.

int solution(vector<vector<int>> sizes) {
    int answer = 0;
    
    int max_w = 0, max_h = 0;
        
    for (int i = 0; i < sizes.size(); ++i) {
        // 가로 < 세로 인 경우 -> 뒤집음
        if (sizes[i][0] < sizes[i][1]) {
            int tmp = sizes[i][0];
            sizes[i][0] = sizes[i][1];
            sizes[i][1] = tmp;
        }
        
        max_w = max(max_w, sizes[i][0]);
        max_h = max(max_h, sizes[i][1]);
    }
    
    answer = max_w * max_h;
    
    return answer;
}