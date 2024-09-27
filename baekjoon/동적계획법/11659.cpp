#include <iostream>

using namespace std;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    int num[n]; 
    int sum[n]; // i번째 까지의 누적합
    for (int i = 0; i < n; ++i) {
        cin >> num[i];
        if (i > 0) {
            sum[i] = num[i] + sum[i-1];
        }
    }

    for (int i = 0; i < m; ++i) {
        int s, e;
        cin >> s >> e;
        cout << sum[e-1] - sum[s-1] + num[s-1] << '\n';
    }

    return 0;
}