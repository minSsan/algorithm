#include <iostream>

using namespace std;

int main() {
    int n; // * 도시의 수
    cin >> n;

    int lenghts[n-1]; // * 도시 간 거리 
    for (int i = 0; i < n-1; ++i) {
        cin >> lenghts[i];
    }

    int prices[n]; // * 각 도시의 기름 값
    for (int i = 0; i < n; ++i) {
        cin >> prices[i];
    }

    // ? 지금까지 거쳐온 도시 중에서, 가장 적은 기름 값을 저장하는 변수.
    // 현재까지의 가장 저렴한 기름 값으로 이동하면 다음 도시를 이동할 때 최소 금액을 사용할 수 있다. 
    int min = prices[0]; // * 지금까지의 가장 저렴한 기름 값을 저장하는 변수
    unsigned long long sum = (unsigned long long) prices[0] * lenghts[0]; // * 총 경비를 저장하는 변수
    // 첫 번째 도시는 무조건 0번째 가격으로 경유해야 하므로, 초기 값을 위와 같이 설정

    for (int i = 1; i < n-1; ++i) {
        if (min > prices[i]) { // ? 현재 밟고 있는 도시의 기름 값이 최소 기름 값보다 적다면
            min = prices[i]; // 최소 기름 값을 갱신
        }
        sum += (unsigned long long) min * lenghts[i];
    }

    cout << sum << '\n';

    return 0;
}