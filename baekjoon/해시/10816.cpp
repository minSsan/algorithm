#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    int n;
    cin >> n;
    unordered_map<int, int> cards;
    for (int i = 0; i < n; ++i) {
        int card;
        cin >> card;
        if (cards.find(card) != cards.end()) {
            cards[card]++;
        } else {
            cards[card] = 1;
        }
    }

    int m;
    cin >> m;
    while (m--) {
        int target;
        cin >> target;
        if (cards.find(target) == cards.end()) cout << "0 ";
        else cout << cards[target] << ' ';
    }
    cout << '\n';
    return 0;
}