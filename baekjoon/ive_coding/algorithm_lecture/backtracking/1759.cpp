#include <iostream>

using namespace std;

// * 암호는 서로 다른 L개의 알파벳 소문자들로 구성되며 
// * 최소 한 개의 모음(a, e, i, o, u)과 최소 두 개의 자음으로 구성
// * 암호를 이루는 알파벳이 암호에서 증가하는 순서로 배열
// * 문자의 종류는 C가지

int l, c; // ? l: 암호의 길이, c: 암호에 사용된 문자의 갯수
bool alphabets[26]; // ? 각 알파벳이 암호에 사용될 수 있는 문자인지 저장하는 배열
bool visited[26]; // ? 암호 안에서 이미 사용된 문자인지 기록하는 배열
char result[15];

bool isVowel(char c) { // 주어진 문자가 모음인지 검사하는 함수
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
        return true;
    }
    return false;
}

char print_c;

void dfs(char now, int vowel, int notVowel) {
    // 문자의 길이가 암호 길이와 동일하면서, 모음이 적어도 하나 존재한다면,
    if (vowel + notVowel == l && vowel > 0) {
        // 암호 출력
        for (int i = 0; i < 26; ++i) {
            if (visited[i]) {
                print_c = 'a' + i;
                cout << print_c;
            }
        }
        cout << '\n';
        return ;
    }

    for (int i = 0; i < 26; ++i) {
        if (alphabets[i] && !visited[i]) { // 아직 'a' + i 문자가 암호에 포함되지 않았다면,
            visited[i] = true;
            if (isVowel('a'+i)) {
                dfs('a' + i, vowel + 1, notVowel);
            } else {
                dfs('a' + i, vowel, notVowel + 1);
            }
            visited[i] = false;
        }
    }
}

int main() {
    cin >> l >> c;
    
    char input_char;
    for (int i = 0; i < c; ++i) {
        cin >> input_char;
        alphabets[input_char - 'a'] = true;
    }

    // * 시작 문자 결정하기
    char start_char;
    for (int i = 0; i < 26; ++i) {
        if (alphabets[i]) {
            start_char = 'a' + i;
        }
    }

    // * 암호 탐색 시작하기
    if (isVowel(start_char)) {
        dfs(start_char, 1, 0);
    } else {
        dfs(start_char, 0, 1);
    }

    return 0;
}