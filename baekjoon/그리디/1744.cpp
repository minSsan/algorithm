#include <iostream>
#include <algorithm>
#include <vector>

//? 음수는 음수끼리, 양수는 양수끼리 곱한다.
//? 음수가 홀수 개인 경우 -> 가장 작은 숫자끼리 곱하고, 남은 하나의 숫자는 그대로 더하거나 0과 곱해서 없앤다.
//? 양수가 홀수 개인 경우 -> 가장 큰 숫자끼리 곱하고, 남은 하나의 숫자는 그대로 더한다.
//? 1은 곱해도 똑같은 숫자이기 때문에, 곱하지 않고 그대로 더하는 것이 이득이다.

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> minus;
    vector<int> plus;
    int one_cnt = 0;
    int zero_cnt = 0;
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        if (num == 1) one_cnt++;
        else if (num > 0) plus.push_back(num);
        else if (num == 0) zero_cnt++;
        else minus.push_back(num);
    }

    sort(minus.begin(), minus.end());
    sort(plus.begin(), plus.end());

    int result = 0;

    //* 1. 음수끼리 곱하기
    int end = minus.size()-1;
    if (!minus.empty() && minus.size() % 2 == 1) {
        if (zero_cnt == 0) {
            result += minus.back();
        }
        end--;
    }
    for (int i = 0; i <= end; i += 2) {
        result += minus[i] * minus[i+1];
    }

    //* 2. 1은 그대로 더하기
    result += one_cnt;

    //* 3. 양수끼리 곱하기
    int start = 0;
    if (!plus.empty() && plus.size() % 2 == 1) {
        result += plus[0];
        start++;
    }

    for (int i = start; i < plus.size(); i += 2) {
        result += plus[i] * plus[i+1];
    }

    cout << result << '\n';

    return 0;
}