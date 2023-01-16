#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// * k개의 가방에 보석을 하나씩만 넣을 수 있다.
// * 담을 수 있는 보석의 최대 가격 구하기

int main() {
    int n, k;
    cin >> n >> k;

    vector<pair<int,int>> ruby(n);
    for (int i = 0; i < n; ++i) {
        cin >> ruby[i].first >> ruby[i].second;
    }
    sort(ruby.begin(), ruby.end()); // 무게가 적은 순으로 정렬

    // // * test code
    // for (int i = 0; i < n; ++i) {
    //     cout << "무게: " << ruby[i].first << " 가격: " << ruby[i].second << '\n';
    // }
    // // * ---------

    vector<int> bags(k);
    for (int i = 0; i < k; ++i) {
        cin >> bags[i];
    }
    sort(bags.begin(), bags.end()); // 가방 무게 한도가 작은 것부터 정렬

    // // * test code
    // for (int i = 0; i < k; ++i) {
    //     cout << "가방" << i << " " << bags[i] << '\n';
    // }
    // // * ---------

    int index = 0;
    long long result = 0;
    priority_queue<int> pq;

    for (int i = 0; i < k; ++i) {
        int weight = bags[i]; 
        while (index < n && ruby[index].first <= weight) {
            pq.push(ruby[index].second); 
            index++;
        }

        if (!pq.empty()) {
            result += pq.top(); 
            pq.pop();
        }
    }

    cout << result << '\n';

    return 0;
}

// ? 적은 무게의 보석은 작은 무게의 가방에 넣는다
// 2 99 -> 10
// 1 65 -> 2
// 5 23

// 2
// 10


// 100 100
// 5 10

// 11

// ? 1. 무게가 적은 순으로 정렬
// 1 65 -> 2
// 2 99 -> 10
// 5 23

// 5 23
// 7 99

// ? 2. 가방을 오름차순으로 정렬
// 2
// 10

// ? 3. 오름차순으로 정렬된 가방들을 순회하여, 자신의 가방 무게보다 무게가 적거나 같은 보석들을 푸시(단, 무게가 높은 순으로)
// 2 -> {2, 99}, {1, 65}
// 다음 가방으로 넘어가기 전에, 앞의 가방 목록에서 top 값의 가격을 result에 더한다음 pop
// 2 -> {1, 65}, result = 99
// 앞 목록에서 남은 보석들을 모두 다음 가방에 먼저 푸시
// 2-> , 10 -> {1, 65}
// 같은 작업 반복
// 10 -> {1, 65}, {5, 23}