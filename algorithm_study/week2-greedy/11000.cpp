#include <iostream>
#include <queue>

using namespace std;

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    
    int n;
    cin >> n;

    int start, end, cnt = 0;
    
		// 강의 시간 목록 (최소힙 - 오름차순)
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> lectures;
    // 각 강의실의 강의 종료 시간 (최소힙)
    priority_queue<int, vector<int>, greater<int>> end_times;

    // 강의 시간을 오름차순으로 정렬한다. push와 동시에 정렬이 이루어짐 (logN)
    for (int i = 0; i < n; ++i) {
        cin >> start >> end;
        lectures.push({start, end});
    }
		
    // 첫 번째 강의실 강의 종료 시간을 end_times에 push
    end_times.push(lectures.top().second);
    // 목록에서 첫 번째 강의 시간을 pop
    lectures.pop();
    // 강의실 수를 1 증가
    cnt++;
	
    // 시간 복잡도 - NlogN (20만 * 약 17 = 약 340만)
    for (int i = 1; i < n; ++i) {
        start = lectures.top().first;
        end = lectures.top().second;

        // 현재 강의 시작 시간이, 앞선 강의들 중 가장 빠른 종료 시간 이후라면,
        if (start >= end_times.top()) {
            // 해당 강의의 바로 뒤에 강의를 배정한다.
            // -> 앞 강의 종료 시간을 무효시킨다.
            end_times.pop();
        } else { // 시간이 겹친다면,
            // 강의실을 추가한다.
            cnt++;
        }
        // 현재 강의 종료시간을 힙에 추가한다.
        end_times.push(end);
        // 다음 강의 시간을 보기 위해, 현재 강의 시간을 pop
        lectures.pop();
    }

    cout << cnt << '\n';
}