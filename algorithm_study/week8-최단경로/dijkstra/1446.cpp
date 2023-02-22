#include <iostream>
#include <vector>

using namespace std;

// * 도착 위치가 길이보다 큰 경우는 무시한다.
// * min_d의 초깃값은 위치값으로 초기화한다 (0부터 해당 위치까지의 거리로)
// ? 0 위치부터 차례대로 각 위치까지의 최단 거리 계산하기
// ? 각 위치에 도달할 때마다, 해당 위치와 연결된 지름길이 있는지 확인
// ? -> 지름길이 존재한다면, end 위치의 min_d 값을 갱신

int n, d; // ? n: 지름길의 갯수, d: 고속도로의 길이

struct node
{
    int distance;
    int number;
};

vector<node> graph[10001]; // 지름길 저장
int min_d[10001]; // 각 위치까지 도달하는 최단 경로

int main() {
    cin >> n >> d;
    
    for (int i = 0; i <= d; ++i) {
        min_d[i] = i; // 지름길을 거치지 않고 그냥 이동했을 때의 거리
    }

    int start, end, distance;
    for (int i = 0; i < n; ++i) {
        cin >> start >> end >> distance;
        if (end <= d) {
            graph[start].push_back({distance, end});
        }
    }

    for (int i = 0; i < d; ++i) {
        if (graph[i].size() > 0) { // i 위치와 연결된 지름길이 존재한다면,
            for (int k = 0; k < graph[i].size(); ++k) {
                end = graph[i][k].number;
                distance = graph[i][k].distance;
                if (min_d[i] + distance < min_d[end]) {
                    min_d[end] = min_d[i] + distance;
                }
            }
        }
        if (min_d[i] + 1 < min_d[i+1]) {
            min_d[i + 1] = min_d[i] + 1;
        }
    }

    cout << min_d[d] << '\n';

    return 0;
}

// * min_d[50] = 10
// * min_d[1] = 1
// * min_d[2] = 2
// * ...
// * min_d[100] = 10 + 10 = 20
// * min_d[51] = 