#include <iostream>
#include <queue>
#include <deque>
#include <vector>

using namespace std;

deque<int> dq;

const int MAX = 100000;
int prev_loc[100001]; // 인덱스 값의 위치를 방문하기 전에 거쳐온 위치를 저장

void bfs(int start, int end) {
    prev_loc[start] = -1;
    dq.push_back(start);

    while (!dq.empty()) {
        int now = dq.front();
        dq.pop_front();

        if (now == end) {
            return ;
        }

        if (now + 1 <= MAX && prev_loc[now + 1] == 0) {
            prev_loc[now + 1] = now;
            dq.push_back(now + 1);
        }

        if (now - 1 >= 0 && prev_loc[now - 1] == 0) {
            prev_loc[now - 1] = now;
            dq.push_back(now - 1);
        }

        if (2 * now <= MAX && prev_loc[2 * now] == 0) {
            prev_loc[2 * now] = now;
            dq.push_back(2 * now);
        }
    }
}

int main() {
    int n, k;
    cin >> n >> k;

    bfs(n, k);

    while (!dq.empty()) {
        dq.pop_back();
    }

    int index = k;
    int cnt = 0;
    while (index != -1) {
        cnt++;
        dq.push_front(index);
        index = prev_loc[index];
    }

    cout << --cnt << '\n';
    
    while (!dq.empty()) {
        cout << dq.front() << ' ';
        dq.pop_front();
    }

    cout << '\n';
    
    return 0;
}