#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int main() {
    string line;
    // ? 한 줄 입력
    getline(cin, line);

    // ? 공백을 기준으로 split
    stringstream ss(line);

    string basic_type;
    ss >> basic_type;

    string variable;
    string result;
    while (ss >> variable) {
        result = basic_type;

        int idx = variable.size() - 2;
        while (!(variable[idx] >= 'A' && variable[idx] <= 'Z' || variable[idx] >= 'a' && variable[idx] <= 'z')) {
            if (variable[idx] == ']') {
                result.push_back('[');
                result.push_back(']');
                idx -= 2;
            } else {
                result.push_back(variable[idx]);
                idx--;
            }
        }

        result.push_back(' ');

        for (int i = 0; i <= idx; ++i) {
            result.push_back(variable[i]);
        }

        cout << result << ";\n";
    }

    return 0;
}