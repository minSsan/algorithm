#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    unordered_map<string, int> name_to_num;
    string num_to_name[n+1];

    for (int i = 1; i <= n; ++i) {
        string poketmon;
        cin >> poketmon;
        name_to_num[poketmon] = i;
        num_to_name[i] = poketmon;
    }

    for (int i = 0; i < m; ++i) {
        string question;
        cin >> question;
        if (isdigit(question[0])) {
            cout << num_to_name[stoi(question)] << '\n';
        } else {
            cout << name_to_num[question] << '\n';
        }
    }

    return 0;
}