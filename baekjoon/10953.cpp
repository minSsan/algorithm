#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

vector<string> split(string str, char delimiter);

int main() {
    int T;
    cin >> T;
    
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}

vector<string> split(string input, char delimiter) {
    vector<string> answer;
    stringstream ss(input);
    string temp;

    while(getline(ss, temp, delimiter)) {
        answer.push_back(temp);
    }

    return answer;
}