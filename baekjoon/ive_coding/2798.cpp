#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, M, result = 0;
    cin >> N >> M;
    
    vector<int> cards(N);
    for (int i = 0; i < N; ++i) {
        cin >> cards[i];
    }

    int sum;

    for (int i = 0; i < N-2; ++i) {
        for (int j = i+1; j < N-1; ++j) {
            for (int k = j+1; k < N; ++k) {
                sum = cards[i] + cards[j] + cards[k];
                if (sum <= M && sum > result) {
                    result = sum;
                }
            }
        }
    }

    cout << result << '\n';
    return 0;
}