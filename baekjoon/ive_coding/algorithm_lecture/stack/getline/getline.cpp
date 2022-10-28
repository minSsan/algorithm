#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
    string s;
    // getline(cin, s);
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin.ignore(); // 입력 한 번 무시 -> getline으로 입력받으면 버퍼에 남기 때문에 무시해야 함
        getline(cin, s);
        cout << s << '\n';
    }

    return 0;
}