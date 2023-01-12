#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int t;
    cin >> t;

    int n;
    
    for (int k = 0; k < t; ++k) {
        cin >> n;

        vector<pair<int, int>> rank(n);
        
        for (int i = 0; i < n; ++i) {
            cin >> rank[i].first >> rank[i].second;
        }

        sort(rank.begin(), rank.end()); // ? 서류 순위 기준 오름차순 정렬
        
        int min_rank = rank[0].second; // ? 현재까지의 면접 순위 최솟값
        int cnt = 1;

        for (int i = 1; i < n; ++i) {
            // ? 순위가 앞 사람보다 더 높다면
            if (rank[i].second < min_rank) {
                cnt++;
                min_rank = rank[i].second;
            }
        }

        cout << cnt << '\n';
    }


    return 0;
}

// * 서류 기준
// 1 4  
// 2 3  
// 3 2  
// 4 1  
// 5 5 

// * 면접 기준
// 4 1 : X
// 3 2 : X
// 2 3 : X
// 1 4 : X
// 5 5 : O

// ! -> 5 5인 애를 떨어뜨리면 최대 4명이 붙을 수 있다.

// * 서류 기준
// 1 4
// 2 5
// 3 6
// 4 2
// 5 7
// 6 1
// 7 3

// * 면접 기준
// 6 1
// 4 2
// 7 3
// 1 4
// 2 5
// 3 6
// 5 7