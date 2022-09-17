#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;

    // N+1 만큼의 길이를 갖는 벡터 -> n번째 자리에는 n킬로그램의 설탕을 담을 때 사용 가능한 최소 봉지 수가 저장되어 있다
    vector<int> min_count(N+1);
    // min_count에 저장된 모든 값을 -1로 초기화
    min_count.assign(N+1, -1);
    
    // 3킬로그램 봉지와 5킬로그램 봉지만 사용할 수 있으므로, 3킬로그램 설탕과 5킬로그램 설탕을 담을 때 사용할 수 있는 최소 봉지 수는 1봉지
    min_count[3] = 1;
    min_count[5] = 1;

    for (int i = 6; i < N+1; ++i) {
        if (min_count[i-3] != -1 && min_count[i-5] != -1) {
            min_count[i] = min_count[i-3] < min_count[i-5] ? min_count[i-3] + 1 : min_count[i-5] + 1;
        }
        else if (min_count[i-3] != -1) {
            min_count[i] = min_count[i-3] + 1;
        } 
        else if (min_count[i-5] != -1) {
            min_count[i] = min_count[i-5] + 1;
        }
    }

    cout << min_count[N] << '\n';

    return 0;
}