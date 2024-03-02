#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

vector<string> split(string str, char delimiter);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    string input;
    vector<string> temp;
    cin >> T;

    for (int i = 0; i < T; ++i) {
        cin >> input;
        temp = split(input, ',');
        cout << stoi(temp[0]) + stoi(temp[1]) << '\n';
    }

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