#include <iostream>
#include <algorithm>
#include <map>
#include <queue>

//? 명제: 가격이 가장 높은 보석은 무게가 가장 높은 가방에 넣는 것이 이득이다.
//* 가격이 높다고 해서 무게가 가볍다는 보장을 할 수 없다. (이 문제에서는 가방에 최대한 알맞는 보석 중 가장 비싼 보석을 넣는 것이 이득)
//* 귀류법: 가격이 가장 높은 보석을, (1) 가방에 넣지 않는 것을 가정(~P) 
//*                               => 보석 가격을 얻을 수 없으므로, 이득이 될 수 없다(모순 O)
//*                           (2) 두 번째로 무거운 가방에 넣는 것을 가정(~P) 
//*                               => 가방에 들어갈 수만 있다면, 더 작은 가방에 넣더라도 얻는 가격은 동일하므로 더 이득이 될 수 없다. 모순을 이끌어낼 수 없음
//* 즉, ~P를 가정했을 때 모순을 이끌어낼 수 없으므로 위 명제는 거짓임
//! <반례> -> 가격이 높고 무게가 가벼운 보석 (10, 1) , 가격이 낮고 무게가 높은 보석 (9, 3) | 가방: 1, 3 => 정답: 19, 명제 답: 10
//!       -> 위의 명제대로라면 3키로 짜리 가방에만 (10, 1) 보석이 들어가고 1키로 짜리 가방은 비어진다.

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    priority_queue<pair<int, int>> diamond; // {가격, 무게}
    for (int i = 0; i < n; ++i) {
        int m, v;
        cin >> m >> v;
        diamond.push({v, m});
    }
    int bags[k];
    for (int i = 0; i < k; ++i) {
        cin >> bags[i];
    }
    sort(bags, bags+k, greater<int>()); // 무게가 큰 가방부터 탐색

    long long result = 0;
    for (int weight : bags) {
        // cout << "가장 무거운 가방: { " << diamond.top().first << ", " << diamond.top().second << " }" << '\n';
        while (!diamond.empty() && diamond.top().second > weight) {
            diamond.pop();
        }
        if (diamond.empty()) {
            cout << result << '\n';
            return 0;
        }

        result += diamond.top().first;
        diamond.pop();
    }

    cout << result << '\n';

    return 0;
}