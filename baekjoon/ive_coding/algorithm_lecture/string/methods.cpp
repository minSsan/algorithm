#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string s;

    cin >> s;

    // 맨 뒤에 문자 추가
    s.push_back('A');
    // 원하는 위치(맨 앞)에 문자 추가
    s.insert(s.begin(), 'A');

    // 문자열 뒤집기
    reverse(s.begin(), s.end());

    // 맨 뒤에 있는 문자 삭제
    s.pop_back();
    // 원하는 위치(맨 앞)에 있는 문자 삭제
    s.erase(s.begin());

    return 0;
}