#include <iostream>

using namespace std;

// * 미래에 현재보다 더 큰 주가가 있다면, 주식을 무조건 산다. 
// * 주가가 가장 클 때는 주식을 판다.

int main() {
    int t;
    cin >> t;

    int n, cnt, sum, max_coin; // ? cnt: 구입한 주식 갯수, sum: 주식을 구입한 금액, max_coin: 최대 주가
    long long result; // ? 최대 수익
    while (t--) {
        // ? 각 케이스에 대해서 모든 변수를 초기화한다.
        cnt = 0;
        sum = 0;
        result = 0;
        
        cin >> n;
        int coins[n]; // ? 날짜별 주가
        for (int i = 0; i < n; ++i) {
            cin >> coins[i];
        }

        // * 앞에서부터 차례대로 주가를 살펴보게 되면, 뒷날에 현재보다 주가가 높은 시점이 있는지 알 수 없다. (중첩 for문은 시간초과) 
        // * 따라서 뒤에서부터 주가를 살펴보는 방법을 채택하였다.
        // 뒷날의 주가보다 낮은 주가일 때는 계속 주식을 하나씩 구매한다.
        // 그러다가 어느 순간 뒷날의 주가보다 더 높아지거나, 모든 주가를 다 살펴본 시점이 오면,
        // 여태 구입한 주식을 모두 판매한 수익을 계산한다. (뒷날의 최대 주가 * cnt - sum)
        max_coin = coins[n-1]; // ? 가장 마지막 날의 주가를 저장
        for (int i = n-2; i >= 0; --i) {
            if (max_coin > coins[i]) { // ? 현재 주가가 최대 주가보다 작다면 -> 무조건 구매
                cnt++; // ? 주식 구매 숫자를 1 증가시킨다. -> 추후 수익을 계산할 때 필요
                sum += coins[i]; // ? 주식을 구입한 금액을 갱신한다. -> 추후 수익을 계산할 때 필요
            } else { // 현재 주가가 미래의 최대 주가보다 더 큰 주가라면,
                result += max_coin * cnt - sum; // ? 수익을 계산한다.
                max_coin = coins[i]; // ? 최대 주가를 갱신한다.
                // 변수 초기화
                cnt = 0;
                sum = 0;
            }
        }

        // 모든 주가를 다 살펴보았다면, 나머지 수익을 계산한다.
        result += max_coin * cnt - sum;

        cout << result << '\n';
    }
    return 0;
}