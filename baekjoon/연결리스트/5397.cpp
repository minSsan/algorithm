#include <iostream>
#include <list>
#include <string>

using namespace std;

int n;

string get_pw(string input) {
    list<char> password;
    list<char>::iterator cursor = password.begin();
    
    for (char c : input) {
        switch (c) {
        case '-':
            if (cursor != password.begin())
                cursor = password.erase(--cursor);
            break;
        case '<':
            if (cursor != password.begin())
                cursor--;
            break;
        case '>':
            if (cursor != password.end())
                cursor++;
            break;
        default:
            password.insert(cursor, c);
            break;
        }
    }

    string result;
    for (char c : password) {
        result += c;
    }
    return result;
}

int main() {
    cin >> n;
    while (n--) {
        string input;
        cin >> input;
        cout << get_pw(input) << '\n';
    }

    return 0;
}