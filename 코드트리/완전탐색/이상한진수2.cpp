#include <iostream>
#include <string>
#include <climits>
#include <algorithm>
#include <cmath>

using namespace std;

// 2진수 string을 10진수로 변환하는 함수
int zerone_to_10(string s) {
    reverse(s.begin(), s.end());
    // 2의 i승
    int result = 0;
    for (int i = 0; i < s.size(); ++i) {
        // i번째 원소에는 2의 i승을 곱하면 된다.
        if (s[i] == '0') continue;

        // 2의 i승 더하기
        result += pow(2, i);
    }
    return result;
}

//? a: 0 이상의 정수 N을 2진법으로 나타낸 뒤, 정확히 한 숫자만을 바꾼 것
//? a를 10진법으로 변환한 N 중에서 최댓값
int main() {
    string a;
    cin >> a;
    int max_num = INT_MIN;
    // i번째 자릿수를 바꾼 경우
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] == '0') a[i] = '1';
        else a[i] = '0';
        max_num = max(max_num, zerone_to_10(a));
        if (a[i] == '0') a[i] = '1';
        else a[i] = '0';
    }

    cout << max_num << '\n';
    return 0;
}