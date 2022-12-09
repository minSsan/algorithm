#include <iostream>
#include <string>

using namespace std;

// ? 대문자로 이루어진 문자열이 있을 때 여기서 최대한 BANANA(B가 1개, N이 2개, A가 3개) 글자들을 몇번 뺄 수 있는지 출력하시오

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    string s;
    cin >> s;

    int cnt = 0, ABN[3] = {0}; // A, B, N 이 각각 몇 개 있는지

    for (char c : s) {
        switch (c) {
            case 'A':
                ABN[0]++;
                break;
                
            case 'B':
                ABN[1]++;
                break;

            case 'N':
                ABN[2]++;
                break;

            default:
                break;
        }
    }

    while (ABN[0] >= 3 && ABN[1] >= 1 && ABN[2] >= 2) {
        cnt++;
        ABN[0] -= 3;
        ABN[1] -= 1;
        ABN[2] -= 2;
    }

    cout << cnt << '\n';

    return 0;
}