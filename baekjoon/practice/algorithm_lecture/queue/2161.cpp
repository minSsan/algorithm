#include <iostream>
#include <queue>

using namespace std;

int main() {
    int n;
    cin >> n;

    queue<int> cards;

    for (int i = 1; i <= n; ++i) {
        cards.push(i);
    }

    while (cards.size() > 1) {
        cout << cards.front() << ' ';
        cards.pop();
        cards.push(cards.front());
        cards.pop();
    }

    cout << cards.front() << '\n';

    return 0;
}