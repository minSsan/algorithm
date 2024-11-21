#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string a, b;
    cin >> a >> b;
    int lcs[a.size()][b.size()];
    fill(lcs[0], lcs[0] + a.size() * b.size(), 0);
    
    if (a[0] == b[0]) {
        lcs[0][0] = 1;
    }

    for (int j = 1; j < b.size(); ++j) {
        if (a[0] == b[j]) {
            lcs[0][j] = 1;
        } else {
            lcs[0][j] = lcs[0][j-1];
        }
    }

    for (int i = 1; i < a.size(); ++i) {
        // margin
        if (a[i] == b[0]) {
            lcs[i][0] = 1;
        } else {
            lcs[i][0] = lcs[i-1][0];
        }

        for (int j = 1; j < b.size(); ++j) {
            if (a[i] == b[j]) {
                lcs[i][j] = lcs[i-1][j-1] + 1;
            } else {
                lcs[i][j] = max(lcs[i][j-1], lcs[i-1][j]);
            }
        }
    }

    int max_len = *minmax_element(lcs[0], lcs[0] + a.size() * b.size()).second;

    string result = "";
    int i = a.size() - 1, j = b.size() - 1;
    while (result.size() != max_len) {
        if (a[i] == b[j]) {
            result += a[i];
            i--; j--;
        } else {
            if (lcs[i][j] == lcs[i-1][j]) {
                i--;
            } else {
                j--;
            }
        }
    }
    reverse(result.begin(), result.end());

    cout << max_len << '\n';
    cout << result << '\n';

    return 0;
}