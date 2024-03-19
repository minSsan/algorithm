#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

bool comp(vector<int> a, vector<int> b) {
    if (a[1] != b[1]) return a[1] < b[1];
    return a[0] < b[0];
}

// 각 시간마다 반복문 실행 -> n초에는 어떤 작업을 수행해야 하는지?
//      -> n초에 수행 가능한 작업 중, 소요시간이 가장 짧은 것을 선택한다. 

// job: [작업이 요청된 시점, 작업의 소요시간]
int solution(vector<vector<int>> jobs) {
    int answer = 0;
    int cnt = jobs.size();
    
    sort(jobs.begin(), jobs.end(), comp);
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // {종료시간, 요청시간}
    int now = 0;
    pair<int, int> job;
    while (!jobs.empty()) {
        // now초 시점에서 어느 작업을 수행할 것인지?
        for (int i = 0; i < jobs.size(); ++i) {
            if (jobs[i][0] <= now) {
                pq.push({now+jobs[i][1], jobs[i][0]});
                jobs.erase(jobs.begin()+i);
                break;
            }
        }
        
        if (pq.empty()) {
            ++now;
            continue;
        }
    
        job = pq.top(); pq.pop();
        
        answer += job.first - job.second; // 종료 시간 - 요청 시간
        now = job.first;
    }
    
    answer = answer / cnt;
    
    return answer;
}