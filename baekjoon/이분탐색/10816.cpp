#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    int cards[n];
    for (int i = 0; i < n; ++i) {
        cin >> cards[i];
    }
    sort(cards, cards+n);

    int m;
    cin >> m;
    while (m--) {
        int target;
        cin >> target;
        int start = 0, end = n-1;
        int mid = (start + end) / 2;

        int cnt = 0;
        while (start <= end) {
            if (cards[mid] == target) {
                cnt++;
                
            }
        }
    }

    return 0;
}