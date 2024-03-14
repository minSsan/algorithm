#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//? 각각의 이모티콘에 할인율을 하나씩 모두 적용 -> 브루트포스
//? 브루트포스로 구한 결과를 모두 answers에 push한 후, 내림차순 정렬 => answer
//?     -> 브루트포스 X 백트래킹으로 변경

vector<vector<int>> answers;
int sale_rate[4] = {10, 20, 30, 40};
int rate[8]; // i번째 이모티콘의 할인 비율
vector<vector<int>> user_info;
vector<int> emoticon_info;

// 현재의 rate 배열 정보를 적용한 결과를 리턴하는 함수
vector<int> get_result() {
    int subscribe=0, buy, total_buy=0;
    // 각 유저의 이모티콘 구매 현황 조사
    for (int i = 0; i < user_info.size(); ++i) {
        buy = 0;
        for (int j = 0; j < emoticon_info.size(); ++j) {
            // i번째 유저가 요구하는 기준보다 할인율이 더 높은 경우
            if (rate[j] >= user_info[i][0]) {
                buy += emoticon_info[j] * (1 - rate[j]*0.01);
            }
        }
        if (buy >= user_info[i][1]) {
            ++subscribe;
        } else {
            total_buy += buy;
        }
    }
    
    return {subscribe, total_buy};
}

void backtracking(int size) {
    if (size == emoticon_info.size()) {
        answers.push_back(get_result());
        return ;
    }
    
    for (int i = 0; i < 4; ++i) {
        rate[size] = sale_rate[i];
        backtracking(size+1);
        rate[size] = 0;
    }
}

bool comp(vector<int> a, vector<int> b) {
    if (a[0] != b[0]) return a[0] > b[0];
    return a[1] > b[1];
}

// users: 사용자들의 구매 기준 [비율, 가격], emoticons: 이모티콘의 정가 정보
// -> 각 유저는 자신이 정한 비율 이상의 할인이 적용된 이모티콘만 구매한다.
// -> 각 유저가 이모티콘을 구매할 시, 기준 가격 이상이 되면 이모티콘 플러스를 가입한다.
vector<int> solution(vector<vector<int>> users, vector<int> emoticons) {
    vector<int> answer; // 최대 플러스 가입자 수, 이모티콘 매출액
    user_info = users; emoticon_info = emoticons;
    
    backtracking(0);
    sort(answers.begin(), answers.end(), comp);
    
    answer = answers[0];
    
    return answer;
}