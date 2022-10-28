#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int cnt = 0, n, m, dp[1000000] = {};
    string str;

    cin >> n >> m >> str;

    for(int i = 0; i < m-2; i++){
        // ? 패턴이 나왔을 때, 
        if(str[i] == 'I' && str[i+1] == 'O' && str[i+2] == 'I'){
            if (i-2 >= 0){
                dp[i] = dp[i-2] + 1; // ? 이전에 나온 패턴 수에 1을 더해서 저장
            } else{
                dp[i] = 1;
            }
        }
        if (dp[i] >= n){
            cnt++;
        }
    }
    
    cout << cnt;

    return 0;
}