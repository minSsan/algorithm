#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string explosion;

string bomb(string message) {
    bool is_bomb;
    
    for (int i = 0; i <= (int) message.size() - (int) explosion.size(); ++i) {
        is_bomb = true;
        for (int j = 0; j < explosion.size(); ++j) {
            if (message[i+j] != explosion[j]) {
                is_bomb = false;
                break;
            }
        }

        if (is_bomb) {
            string front = message.substr(0, i);
            int back_size = message.size() - (i + explosion.size());
            string back = message.substr(i + explosion.size(), back_size);
            message = front + back;
            i = i - explosion.size() - 1;
            i = max(i, -1);
        }
    }
    return message;
}

int main() {
    string message;
    cin >> message >> explosion;

    string result = bomb(message);
    if (result.size() > 0) cout << bomb(message) << '\n';
    else cout << "FRULA\n";

    return 0;
}