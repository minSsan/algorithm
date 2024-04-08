#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// 배달을 다니면서 빈 재활용 택배 상자를 수거
// 배달할 택배는 모두 상자에 담겨서 물류창고에 보관되어 있다.
// 트럭에는 재활용 택배 상자를 최대 cap개 실을 수 있다.
// 각 집마다 배달할 상자 수, 수거할 상자 수가 주어진다.
// 트럭 하나로 모든 배달 및 수거를 마치고 돌아올 수 있는 최소 이동거리를 구한다.

//? 물류창고에서 출발할 때는 무조건 상자를 싣는 것이 이득
//? 멀리 있는 집을 최대한 빨리 0으로 만드는 것이 이득
// 1. 배달하기
//? 가장 멀리 있는 집부터 탐색한다.
//?     -> cap 이하가 될 때까지 필요한 배달 물품 수를 누적해서 더한다.
//?     -> 누적합만큼 배달을 시작한다.
//?     -> 이동거리 = 배달하는 집 중 가장 먼 집의 거리 * 2
// 2. 수거하기
//? 가장 멀리 있는 집부터 탐색한다.
//?     -> cap 이하가 될 때까지 수거할 물품 수를 누적해서 더한다.

int total_del, total_pick;

// cap: 트럭에 실을 수 있는 상자의 최대 개수
// n: 배달할 집의 개수
// deliveries: 각 집에 배달할 상자 개수
// pickups: 각 집에서 수거할 상자 개수
long long solution(int cap, int n, vector<int> deliveries, vector<int> pickups) {
    long long answer = 0;
    
    int delivered = 0, picked = 0;
    for (int i = 0; i < n; ++i) {
        total_del += deliveries[i];
    }
     for (int i = 0; i < n; ++i) {
        total_pick += pickups[i];
    }
    
    int pick, dist, del;
    while (!(delivered == total_del && picked == total_pick)) {
        // 1. 배달하기
        pick = 0; // 몇 개 픽업?
        del = 0; // 몇 개 배달?
        dist = 0; // 몇 번 집까지 이동?
        for (int i = n-1; i >= 0; --i) {
            if (deliveries[i] == 0 && pickups[i] == 0) {
                continue;
            }
            // 배달
            if (del + deliveries[i] <= cap) {
                del += deliveries[i];
                deliveries[i] = 0;
            } else {
                deliveries[i] -= (cap - del);
                del = cap;
            }
            // 수거
            if (pick + pickups[i] <= cap) {
                pick += pickups[i];
                pickups[i] = 0;
            } else {
                pickups[i] -= (cap - pick);
                pick = cap;
            }
            dist = max(dist, i+1);
        }
        delivered += del; picked += pick;

        answer += (dist*2);
    }
    
    return answer;
}