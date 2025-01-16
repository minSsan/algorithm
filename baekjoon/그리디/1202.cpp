#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

//? 현재 가방에 넣을 수 있는 보석 중에서, 가장 비싼 보석을 넣는다.
//?     -> 여기서 선택되지 않은 보석은, 뒤에 가방(= 더 무거운 가방)에도 넣을 수 있음
//?         즉, 값이 충분히 비싸다면 언젠가는 선택됨

int main() {
    int n, k;
    cin >> n >> k;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // {무게, 가격}}
    for (int i = 0; i < n; ++i) {
        int w, v;
        cin >> w >> v;
        pq.push({w, v});
    }

    int bags[k];
    for (int i = 0; i < k; ++i) {
        cin >> bags[i];
    }

    sort(bags, bags+k);

    long long result = 0;
    priority_queue<int> coord;
    for (int i = 0; i < k; ++i) {
        int weight = bags[i];

        // 남은 보석이 없는 경우 -> coord에 남은 보석을 남은 가방에 모두 넣기
        if (pq.empty()) {
            for (int j = 0; j < k-i; ++j) {
                if (!coord.empty()) {
                    result += coord.top();
                    coord.pop();
                }
            }
            break;
        }

        // 현재 보석의 무게가 가방 무게를 초과하는 경우 -> 다음 가방
        if (pq.top().first > weight) {
            // 앞에서 넣지 않은 보석이 있는 경우 -> 현재 가방에 추가
            if (!coord.empty()) {
                result += coord.top();
                coord.pop();
            }
            continue;
        }

        // 현재 가방에 넣을 수 있는 보석을 후보에 모두 추가하기
        while (!pq.empty() && pq.top().first <= weight) {
            coord.push(pq.top().second);
            pq.pop();
        }
        // 넣을 수 있는 보석 중 가장 비싼 보석 넣기
        result += coord.top();
        coord.pop();
    }

    cout << result << '\n';

    return 0;
}