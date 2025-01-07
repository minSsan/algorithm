#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string s;
    cin >> s;

    int start = 0, sum = 0;
    vector<int> nums;

    //* 첫 번째 숫자 더하기
    int idx = 0;
    while (idx < s.size() && s[idx] != '-' && s[idx] != '+') {
        idx++;
    }
    nums.push_back(stoi(s.substr(start, idx)));

    for (int i = idx; i < s.size(); ++i) {
        if (s[i] == '+') {
            idx = i+1;
            while (idx < s.size() && s[idx] != '-' && s[idx] != '+') {
                idx++;
            }
            int num = stoi(s.substr(i+1, idx - i - 1));
            nums.push_back(num);
            i = idx-1;
            continue;
        }

        if (s[i] == '-') {
            //* 다음 '-'가 나올 때까지 모두 더한다.
            i++;
            start = i;
            int tmp = 0;
            while (i < s.size() && s[i] != '-') {
                if (s[i] == '+') {
                    // cout << "- 뒤에 있는 숫자: " << s.substr(start, i - start) << '\n';
                    tmp += stoi(s.substr(start, i - start));
                    start = i+1;
                }
                i++;
            }
            // cout << "- 뒤에 있는 숫자: " << s.substr(start, i - start) << '\n';
            tmp += stoi(s.substr(start, i - start));

            //* 더한 값에 -1을 곱한 값을 nums에 추가한다.
            nums.push_back(-1 * tmp);
            i--;
        }
    }

    int result = 0;
    for (int num : nums) {
        result += num;
    }

    cout << result << '\n';

    return 0;
}