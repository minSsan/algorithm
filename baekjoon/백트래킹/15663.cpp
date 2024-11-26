#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <string>

using namespace std;

int n, m;
int nums[10];
bool visited[10]; // i번째 숫자 사용 여부
vector<int> v;
set<string> results;

string v_to_str() {
    string result = "";
    for (int num : v) {
        result.append(to_string(num) + " ");
    }
    return result;
}

void dfs() {
    if (v.size() == m) {
        string result = v_to_str();
        results.insert(result);
        return ;
    }
    
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            v.push_back(nums[i]);
            visited[i] = true;
            dfs();
            v.pop_back();
            visited[i] = false;
        }
    }
}

bool compare(string a, string b) {
    vector<int> a_nums;
    vector<int> b_nums;

    int start_index = 0;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] == ' ' || i == a.size()-1) {
            a_nums.push_back(stoi(a.substr(start_index, i - start_index)));
            start_index = i+1;
        }
    }
    start_index = 0;
    for (int i = 0; i < b.size(); ++i) {
        if (b[i] == ' ' || i == b.size()-1) {
            b_nums.push_back(stoi(b.substr(start_index, i - start_index)));
            start_index = i+1;
        }
    }

    return a_nums < b_nums;
}

int main() {
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    sort(nums, nums + n);

    dfs();

    vector<string> tmp(results.begin(), results.end());
    sort(tmp.begin(), tmp.end(), compare);
    
    for (string value : tmp) {
        cout << value << '\n';
    }

    return 0;
}