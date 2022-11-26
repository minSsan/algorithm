#include <iostream>
#include <vector>

using namespace std;

int main() {
    int T;
    cin >> T;

    vector<vector<int>> arr;

    int N, input_num;
    long long result;

    int bought_price, bought_num;
    int max_price_idx;

    for (int r = 0; r < T; ++r) {
        cin >> N;
        vector<int> row;
        
        result = 0;
        bought_num = 0;
        bought_price = 0;
        max_price_idx = 0;

        for (int i = 0; i < N; ++i) {
            cin >> input_num;
            row.push_back(input_num);
        }
        arr.push_back(row);

        for (int c = 0; c < N - 1; ++c) {
            if (arr[r][c] <= arr[r][c+1]) {
                if (c == N - 2) {
                    if (max_price < arr[r][c+1]) {
                        max_price = arr[r][c+1];
                    }
                    // result += arr[r][c+1] * bought_num - bought_price;
                }
            } else {
                if (arr[r][max_price_idx] < arr[r][c]) {
                    max_price_idx = c;
                }
            }
        }

        result += max_price * bought_num - bought_price;

        cout << result << '\n';
    }

    return 0;
}
// c = 2 , result = 
// num = 2 , price = 2