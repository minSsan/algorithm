#include <string>
#include <vector>

using namespace std;

// 행사 목표
// 1순위: 이모티콘 플러스 서비스 가입자를 최대한 늘리기
// 2순위: 이모티콘 판매액을 최대한 늘리기

// ? - 각 이모티콘에 대해서 1퍼센트 ~ 40퍼센트 할인을 할 때 가장 목표 달성이 잘 되는 퍼센트 구하기
// ?   -> 앞에서 구한 퍼센트보다 가입자가 더 많다면, 가입자랑 판매액을 갱신

// + 이모티콘마다 할인율은 다를 수 있으며, 할인율은 10%, 20%, 30%, 40% 중 하나로 설정
//   -> 이모티콘 갯수만큼 할인율 조합을 만들어야 함 (ex. 이모티콘 2개 -> [10, 10], [10, 20], [10, 30], [10, 40], ..., [40, 40])

int emoticon_cnt;
int dc_rates[4] = {10, 20, 30, 40};
bool visited[4]; // 10, 20, 30, 40 포함 되어있는지 안 되어 있는지
vector<int> dc_set;
vector<vector<int>> dc_sets;

void dijkstra(int cnt) { 
    if (cnt == emoticon_cnt) {
        dc_sets.push_back(dc_set);
        return ;
    }

    for (int i = 0; i < 4; ++i) {
        dc_set.push_back(dc_rates[i]);
        dijkstra(cnt + 1);
        dc_set.pop_back();
    }
}

vector<int> solution(vector<vector<int>> users, vector<int> emoticons) {
    vector<int> answer;
    
    emoticon_cnt = emoticons.size();
    dijkstra(0);
    
    int max_register = 0;
    int max_price = 0;
    
    for (int dc_index = 0; dc_index < dc_sets.size(); ++dc_index) {
        // dc_sets[dc_index] 의 할인율 조합으로 진행하는 경우의 가입자 수
        int current_people = 0;
        // dc_sets[dc_index] 의 할인율 조합으로 진행하는 경우의 총 구매비용
        int current_price = 0;
        
        for (int i = 0; i < users.size(); ++i) {
            // 현재 사용자가 구매한 이모티콘의 총액
            int total_price = 0;
            
            int user_dc = users[i][0]; // user_dc % 이상 할인할 때만 구매
            int user_min_price = users[i][1];
            
            // 각 이모티콘의 할인율을 확인하여 구매 여부 결정
            for (int j = 0; j < emoticons.size(); ++j) {
                int dc_rate = dc_sets[dc_index][j]; // j번째 이모티콘의 할인율
                if (dc_rate >= user_dc) { // 할인율이 사용자가 요구하는 할인율 이상일 때
                    total_price += emoticons[j] - dc_rate * (emoticons[j] / 100); 
                }
            }
            
            // user_min_price 이상이 되면 구매 모두 취소 후, 구독
            if (total_price >= user_min_price) {
                current_people++;
            } else {
                current_price += total_price;
            }
        }
        
        if (current_people > max_register) {
            max_register = current_people;
            max_price = current_price;
        } else if (current_people == max_register && current_price > max_price) {
            max_price = current_price;
        }
    }
    
    answer.push_back(max_register);
    answer.push_back(max_price);
    
    return answer;
}