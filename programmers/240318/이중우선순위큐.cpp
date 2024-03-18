#include <string>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

bool comp(int a, int b) {
    return a > b;
}

// 명령어
struct command {
    char op; // 연산
    int num; // 숫자
};

// 문자열을 command 구조체로 변환하는 함수
command str_to_command(string s) {
    command c;
    c.op = s.substr(0, 1)[0];
    c.num = stoi(s.substr(2, s.size()-2));
    return c;
}

// I 숫자:   숫자 삽입
// D 1:     큐에서 최댓값 삭제
// D -1:    큐에서 최솟값 삭제
// * 최댓값, 최솟값이 둘 이상인 경우 하나만 삭제한다.
// * 빈 큐에서 데이터를 삭제하라는 명령 -> 무시

// 모든 연산을 처리한 후 
//  큐가 비어있으면 [0, 0]
//  비어있지 않으면 [최댓값, 최솟값] 리턴
vector<int> solution(vector<string> operations) {
    vector<int> answer;
    
    //? 최대힙 & 최소힙 분리? -> 다른 힙에서는 삭제되지 않는 문제.
    //? 방문처리? -> 음수 값도 들어올 수 있음
    //? 최댓값 삭제 횟수 & 최솟값 삭제 횟수 저장? -> 놉(사잇값 들어오면 꼬임)
    //? deque? -> 값을 뺄 때마다 정렬(N*NlogN)
    
    deque<int> dq;
    for (int i = 0; i < operations.size(); ++i) {
        command c = str_to_command(operations[i]);
        if (c.op == 'I') {
            dq.push_back(c.num);
        }
        else if (c.op == 'D') {
            if (dq.empty()) continue;
            sort(dq.begin(), dq.end());
            if (c.num == -1) {
                dq.pop_front();
            } else {
                dq.pop_back();
            }
        }
    }
    
    if (dq.empty()) return {0, 0};
    sort(dq.begin(), dq.end());
    answer = {dq.back(), dq.front()};
    
    return answer;
}