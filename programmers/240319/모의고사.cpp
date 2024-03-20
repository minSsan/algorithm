#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(pair<int, int> a, pair<int, int> b) {
    return a.first > b.first;
}

// 1번 수포자: 1 - 2 - 3 - 4 - 5 - ...
// 2번 수포자: 2 - 1 - 2 - 3 - 2 - 4 - 2 - 5 - ... (2와 2제외 1~5를 번갈아서)
// 3번 수포자: 3 - 3 - 1 - 1 - 2 - 2 - 4 - 4 - 5 - 5 - ... (3,1,2,4,5 순서로 두 개씩)
int first[5] = {1, 2, 3, 4, 5};
int second[8] = {2, 1, 2, 3, 2, 4, 2, 5};
int third[10] = {3, 3, 1, 1, 2, 2, 4, 4, 5, 5};

// answers 에 있는 정답과 찍은 답지와 매칭이 가장 많이 된 사람을 구한다.
vector<int> solution(vector<int> answers) {
    vector<int> answer;
    
    vector<pair<int, int>> result; // {최종 점수, 번호}
    for (int i = 1; i <= 3; ++i) result.push_back({0, i});
    
    // 답안지 크기만큼 세 사람의 답안지를 작성
    int first_index = 0, second_index = 0, third_index = 0;
    for (int i = 0; i < answers.size(); ++i) {
        if (answers[i] == first[first_index]) {
            ++result[0].first;
        }
        if (answers[i] == second[second_index]) {
            ++result[1].first;
        }
        if (answers[i] == third[third_index]) {
            ++result[2].first;
        }
        
        first_index = (first_index+1) % 5;
        second_index = (second_index+1) % 8;
        third_index = (third_index+1) % 10;
    }
    
    // 점수 기준 내림차순 정렬
    sort(result.begin(), result.end(), comp);
    
    answer.push_back(result[0].second);
    int max_score = result[0].first;
    for (int i = 1; i < 3; ++i) {
        if (result[i].first == max_score) answer.push_back(result[i].second);
    }
    
    sort(answer.begin(), answer.end());
    
    return answer;
}