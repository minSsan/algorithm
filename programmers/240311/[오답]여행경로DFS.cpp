#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

//? 가능한 경로는 여러 개 나올 수 있음 -> 그 중에서도 사전순으로 앞서는 것으로 선택
//?     -> 가능한 경로를 모두 탐색해야 하므로 DFS
//? 주어진 항공권을 모두 사용해야 -> 각 항공권의 사용 여부를 기록해야 함

using namespace std;

int ticket_size, current_index;
vector<string> current_ticket;
string next_start; // 다음 출발지
bool used[10000]; // i번째 티켓의 사용 여부
vector<vector<int>> answers; // 경로 - 인덱스
vector<vector<string>> answers_str; // 경로 - 공항이름

vector<vector<string>> index_to_str(vector<vector<string>> &tickets, vector<vector<int>> answers) {
    vector<vector<string>> answer;
    vector<string> path;
    for (int i = 0; i < answers.size(); ++i) {
        for (int j = 0; j < ticket_size; ++j) {
            int ticket_index = answers[i][j];
            path.push_back(tickets[ticket_index][0]);
            if (j == ticket_size-1) {
                path.push_back(tickets[ticket_index][1]);
            }
        }
        answer.push_back(path);
    }
    return answer;
}

void print(vector<int> used_index) {
    cout << "[ ";
    for (int i = 0; i < used_index.size(); ++i) {
        cout << used_index[i] << ", ";
    }
    cout << " ]";
}

void dfs(vector<vector<string>> &tickets, vector<int> used_index) {
    print(used_index);
    
    // 티켓을 모두 사용했다면
    if (used_index.size() == ticket_size) {
        answers.push_back(used_index);
        return ;
    }
    
    if (used_index.size() == 0) {
        next_start = "ICN";
    } else {
        current_index = used_index[used_index.size()-1];
        current_ticket = tickets[current_index];
        next_start = current_ticket[1];
    }
    
    for (int i = 0; i < ticket_size; ++i) {
        // i번째 티켓의 출발지가 next_start + i번째 티켓을 아직 사용하지 않은 경우
        if (next_start == tickets[i][0] && !used[i]) {
            used_index.push_back(i);
            used[i] = true;
            dfs(tickets, used_index);
            used[i] = false;
            used_index.pop_back();
        }
    }
}

vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;
    ticket_size = tickets.size();
        
    dfs(tickets, {});
    
    answers_str = index_to_str(tickets, answers);
    cout << "size >> " << answers.size() << '\n'; 
    sort(answers_str.begin(), answers_str.end());
    
    answer = answers_str[0];
    
    return answer;
}