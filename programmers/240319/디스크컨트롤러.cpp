#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

bool comp_basic(vector<int> a, vector<int> b) {
    if (a[0] != b[0]) return a[0] < b[0];
    return a[1] < b[1];
}

// 각 시간마다 반복문 실행 -> n초에는 어떤 작업을 수행해야 하는지?

bool used[500];

// job: [작업이 요청된 시점, 작업의 소요시간]
int solution(vector<vector<int>> jobs) {
    int answer = 0;
    
    // 맨 처음 작업 고르기
    int start_time, job_time;
    sort(jobs.begin(), jobs.end(), comp_basic);
    start_time = jobs[0][0]; job_time = jobs[0][1];
    answer = job_time;
    used[0] = true;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    int now = start_time+job_time;
    pair<int, int> job;
    while (now <= 500000) {
        // now초 시점에서 어느 작업을 수행할 것인지?
        for (int i = 0; i < jobs.size(); ++i) {
            if (!used[i] && jobs[i][0] <= now) {
                pq.push({now+jobs[i][1], i});
            }
        }
        
        if (pq.empty()) {
            ++now;
            continue;
        }
    
        job = pq.top();
        
        answer += job.first - jobs[job.second][0]; // 종료 시간 - 요청 시간
        now = job.first;
        used[job.second] = true;
        
        while (!pq.empty()) pq.pop();
    }
    
    answer = answer / jobs.size();
    
    return answer;
}