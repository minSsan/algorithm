#include <string>
#include <vector>
#include <iostream>

using namespace std;

// 카펫의 갈색 격자 수, 노란 격자 수가 주어짐
// -> 카펫의 가로, 세로 크기를 배열에 담아 리턴
// 가로 >= 세로

// brown 수 = (가로) * 2 + (세로) * 2 - 4
//? 1. 위 방정식을 만족하는 가로, 세로의 크기를 구해서(가로 >= 세로) 후보군을 만든다.
//? 2. 각 후보군에 대해 노란색 타일 수가 만족하는지 구한다. 
//?     -> (가로) * (세로) - brown == yellow
//? 3. 만족하는 후보를 찾으면 해당 값들을 리턴하고 종료
vector<int> solution(int brown, int yellow) {
    vector<int> answer;
    vector<pair<int, int>> coord; // 후보군 {가로, 세로}
    
    // 1. 후보군 만들기
    for (int h = 1; h <= brown; ++h) {
        for (int w = h; w <= brown; ++w) {
            if (brown == 2*(w+h)-4) {
                cout << "[push] w: " << w << ", h: " << h << '\n';
                coord.push_back({w, h});
            }
        }
    }
    
    int w, h;
    // 2. 후보군 중에서 yellow 값도 만족하는 후보 찾기
    for (int i = 0; i < coord.size(); ++i) {
        w = coord[i].first; h = coord[i].second;
        if (w*h - brown == yellow) {
            return {w, h};
        }
    }
    
    return answer;
}