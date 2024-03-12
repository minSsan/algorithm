#include <string>
#include <vector>

using namespace std;

int term_info[26]; // term_info[0]: 'A' 약관의 유효기간

struct date {
    int year;
    int month;
    int day;
};

date today_info;

// str = YYYY.MM.DD
date str_to_date(string str) {
    date result;
    // year
    result.year = stoi(str.substr(0, 4)); // 0번째부터 네 글자는 year
    // month
    result.month = stoi(str.substr(5, 2));
    // day
    result.day = stoi(str.substr(8, 2));
    
    return result;
}

// date 구조체를 일 수로 바꿔주는 함수
int date_to_day(date d) {
    int year = d.year * 28 * 12;
    int month = d.month * 28;
    return year + month + d.day;
}

// 입력받은 date 정보 + 약관 달 수를 today info와 비교하여 보관 가능한지 판별하는 함수
bool can_keep(date date_info, char term_name) {
    int plus_day = term_info[term_name-'A'] * 28;
    if (date_to_day(date_info) + plus_day > date_to_day(today_info)) {
        return true;
    }
    return false;
}

//? 유효기한의 year, month, day 가 모두 크거나 같아야 보관 가능

vector<int> solution(string today, vector<string> terms, vector<string> privacies) {
    today_info = str_to_date(today);
    // terms (<= 20) - "약관종류 유효기간" ex. "A 12"(A약관, 12달)
    //      유효기간은 100달 이하
    // privacies (<= 100) - "i+1번 개인정보 수집 일자 약관종류" ex. "2021.11.11 A"
    // MM, DD - 한 자릿수는 앞에 0이 붙음
    vector<int> answer;
    char term_name;
    string term_str;
    
    //1. 각 약관의 유효기간 저장
    for (int i = 0; i < terms.size(); ++i) {
        term_name = terms[i].substr(0,1)[0];
        term_str = terms[i].substr(2, terms[i].size()-2);
        term_info[term_name-'A'] = stoi(term_str);
    }
    
    //2. 개인정보 정보 확인
    for (int i = 0; i < privacies.size(); ++i) {
        term_str = privacies[i].substr(0, 10);

        if (!can_keep(str_to_date(term_str), privacies[i].substr(11, 1)[0])) {
            answer.push_back(i+1);
        }
    }
    
    return answer;
}