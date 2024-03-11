#include <string>
#include <vector>

using namespace std;

bool used[10000]; // i번째 티켓의 사용여부
int ticket_cnt;
string min_answer = "a"; // 소문자 아스키 코드 > 대문자 아스키 코드

void dfs(vector<vector<string>> &tickets, string path, string next_start, int cnt) {
    if (cnt == ticket_cnt) {
        if (path < min_answer) min_answer = path+next_start;
        return ;
    }
    
    for (int i = 0; i < tickets.size(); ++i) {
        if (!used[i] && tickets[i][0] == next_start) {
            used[i] = true;
            dfs(tickets, path+tickets[i][1], tickets[i][1], cnt+1);
            used[i] = false;
        }
    }
}

vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;
    ticket_cnt = tickets.size();
    
    dfs(tickets, "ICN", "ICN", 0);
    
    for (int i = 0; i < min_answer.size()-3; i += 3) {
        answer.push_back(min_answer.substr(i, 3));
    }
    
    return answer;
}