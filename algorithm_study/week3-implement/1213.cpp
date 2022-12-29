#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    int cnt[26] = {0};
    string text;
    cin >> text;

    for (char c : text) {
        cnt[c - 'A']++;
    }

    char center;
    string front;
    string back;
    bool exist = true;

    for (int i = 0; i < 26; ++i) {
        if (cnt[i] == 0) continue;

        if (cnt[i] % 2 == 0) {
            while (cnt[i] != 0) {
                front.push_back(char(i + 'A'));
                back = char(i + 'A') + back;
                cnt[i] -= 2;
            }
        } else if (cnt[i] % 2 == 1 && !center) {
            center = char(i + 'A');
            cnt[i]--;
            while (cnt[i] != 0) {
                front.push_back(char(i + 'A'));
                back = char(i + 'A') + back;
                cnt[i] -= 2;
            }
        } else {
            exist = false;
        }
    }

    if (!exist) {
        cout << "I'm Sorry Hansoo\n"; 
    } else {
        cout << front + center + back << '\n';
    }

    return 0;
}