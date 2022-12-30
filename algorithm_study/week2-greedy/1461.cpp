#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

 // * push_back으로 원소를 넣으면, size를 출력할 때 잘못된 값으로 출력된다. 
 // * -> 따라서, 벡터의 가용범위를 먼저 지정해준 후에, push_back으로 원소를 추가하고 size를 출력하면 원소의 개수를 제대로 출력할 수 있다.

int main() {
    int n, m; // n: 책의 수, m: 한번에 들 수 있는 책의 수
    cin >> n >> m;

    vector<int> negative(n); // 음수 위치
    vector<int> positive(n); // 양수 위치

    int input_num;
    for (int i = 0; i < n; ++i) {
        cin >> input_num;
        if (input_num > 0) {
            positive.push_back(input_num);
        } else {
            negative.push_back(input_num);
        }
    }

    int result = 0;

    // ? 각각 오름차순으로 정렬 -> 절댓값이 큰 것부터 처리해야하기 때문
    if (negative.size() > 0) {
        sort(negative.begin(), negative.end());
    }
    if (positive.size() > 0) {
        // 양수는 편의상 내림차순으로 정렬
        sort(positive.begin(), positive.end());
        reverse(positive.begin(), positive.end());
    }

    int negative_index = 0, positive_index = 0; // 음수 위치 배열에서 현재 가리키는 책 인덱스, 양수 위치 배열에서 현재 가리키는 책 인덱스
    // ? 절댓값이 가장 큰 것은 마지막에 방문
    if (negative.size() == 0) {
        result += positive[0];
        positive_index += m;
    } else if (positive.size() == 0) {
        result += -1 * negative[0];
        negative_index += m;
    } else {
        if (-1 * negative[0] > positive[0]) {
            result += -1 * negative[0];
            negative_index += m;
        } else {
            result += positive[0];
            positive_index += m;
        }
    }

    while (negative_index <= negative.size() - 1 || positive_index <= positive.size() - 1) {
        if (negative_index <= negative.size() - 1) {
            result += -1 * negative[negative_index] * 2;
            negative_index += m;
        }

        if (positive_index <= positive.size() - 1) {
            result += positive[positive_index] * 2;
            positive_index += m;
        }
    }

    cout << result << '\n';

    return 0;
}