#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// * 집 N개가 수직선 위에 존재, 같은 좌표에 여러 집 X
// * 공유기 C개를 설치 -> 가장 인접한 두 공유기 사이의 거리를 가능한 크게 하여 설치하려고 한다.
// * 가장 인접한 두 공유기 사이의 거리를 최대로 하는 프로그램

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, c; // n: 집의 개수, c: 공유기의 개수
    cin >> n >> c;
    vector<int> coordinate(n);

    for (int i = 0; i < n; ++i) {
        cin >> coordinate[i];
    }

    sort(coordinate.begin(), coordinate.end());



    return 0;
}