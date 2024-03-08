#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<vector<int>> coord;
vector<vector<string>> answers;

// index 번째 티켓을 사용했는지 확인
bool used(int index, vector<int> v) {
    return find(v.begin(), v.end(), index) != v.end();
}

void set_answers(vector<vector<string>> &tickets) {
    for (int i = 0; i < coord.size(); ++i) {
        vector<string> v;
        for (int j = 0; j < coord[i].size(); ++j) {
            v.push_back(tickets[coord[i][j]][0]);
            if (j == coord[i].size()-1) v.push_back(tickets[coord[i][j]][1]);
        }
        answers.push_back(v);
    }
}

vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;
        
    queue<vector<int>> q; // 경로 - 티켓 번호로 표현
    for (int i = 0; i < tickets.size(); ++i) {
        if (tickets[i][0] == "ICN") {
            q.push({i});
        }
    }
    vector<int> ticket_list;
    string start;
    while(!q.empty()) {
        ticket_list = q.front(); q.pop();
        if (ticket_list.size() == tickets.size()) {
            coord.push_back(ticket_list);
            continue;
        }
        
        start = tickets[ticket_list[ticket_list.size()-1]][1];
        for (int i = 0; i < tickets.size(); ++i) {
            if (used(i, ticket_list)) continue;
            if (tickets[i][0] == start) {
                vector<int> temp(ticket_list.begin(), ticket_list.end());
                temp.push_back(i);
                q.push(temp);
            }
        }
    }
    
    set_answers(tickets);
    sort(answers.begin(), answers.end());
    answer = answers[0];
    
    return answer;
}