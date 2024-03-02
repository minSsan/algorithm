#include <iostream>
#include <algorithm>

using namespace std;

// * 암호는 서로 다른 L개의 알파벳 소문자들로 구성되며 
// * 최소 한 개의 모음(a, e, i, o, u)과 최소 두 개의 자음으로 구성
// * 암호를 이루는 알파벳이 암호에서 증가하는 순서로 배열
// * 문자의 종류는 C가지

int l, c; // ? l: 암호의 길이, c: 암호에 사용 가능한 알파벳 갯수
char alphabets[15]; // ? 암호에 사용 가능한 알파벳들 (사전 오름차순으로 저장)
bool visited[15]; // ? 각각의 문자가 암호에 사용되었는지 저장하는 배열 (각 문자에 대응되는 순서는 alphabets와 동일)
char result[15]; // ? 완성된 암호를 저장하는 배열

bool isVowel(char c) { // 주어진 문자가 모음인지 검사하는 함수
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
        return true;
    }
    return false;
}

// ? l: 4, c: 6 
// ? alphabets: a c i s t w
// ? visited:   t t f t f f
// ? result: a c s 

void dfs(int index, int alphabet_index, int vowel) {
    if (index == l) { // 하나의 암호가 완성되었다면, 암호 출력 후 함수 종료
        if (vowel > 0 && index - vowel >= 2) { // 단, 조건에 성립하는 경우에만 출력한다.
            for (int i = 0; i < l; ++i) {
                cout << result[i];
            }
            cout << '\n';
        }
        return ;
    }

    for (int i = alphabet_index; i < c; ++i) {
        if (!visited[i]) {
            visited[i] = true;
            result[index] = alphabets[i];
            if (isVowel(alphabets[i])) {
                dfs(index + 1, i + 1, vowel + 1);
            } else {
                dfs(index + 1, i + 1, vowel);
            }
            visited[i] = false;
            result[index] = 0;
        }
    }
}

int main() {
    cin >> l >> c;

    for (int i = 0; i < c; ++i) {
        cin >> alphabets[i];
    }

    sort(alphabets, alphabets + c); // 사전상 오름차순으로 정렬해두기
    // a, c, i, s, t, w

    dfs(0, 0, 0);

    return 0;
}