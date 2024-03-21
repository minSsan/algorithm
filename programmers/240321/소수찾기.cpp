#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <set>

using namespace std;

bool isPrime(int num) {
    if (num == 0 || num == 1) return false;
    
    for (int i = 2; i <= sqrt(num); ++i) {
        if (num % i == 0) return false;
    }
    return true;
}

int bound; // 숫자의 길이

//? 1 <= numbers.size() <= 7 , 0-9사이 숫자로만 이뤄짐
//? numbers에 적힌 숫자들을 조합해서 만들 수 있는 소수의 개수
//?  -> numbers에 적힌 숫자들로, 가능한 모든 숫자 조합을 만든다. 
//?     길이가 1부터 numbers.size() 만큼의 길이를 가지는 숫자를 모두 만든 후, 소수 체크 진행
//?     단, 첫 번째 숫자는 0이 되면 안 됨.

string _numbers;
set<int> result; // 소수 후보군
set<int>::iterator iter;
bool visited[7]; // n번 인덱스의 숫자를 방문했는지?

void dfs(string s) {
    if (s.size() == bound) {
        if (s[0] != '0') {
            result.insert(stoi(s));
        }
        return ;
    }
    
    for (int i = 0; i < _numbers.size(); ++i) {
        // if (_numbers[i] == '0' && s.size() == 0) continue;
        
        if (!visited[i]) { // 만약 numbers[i]를 사용하지 않았다면
            visited[i] = true;
            s.push_back(_numbers[i]);
            dfs(s);
            visited[i] = false;
            s.pop_back();
        }
    }
}

int solution(string numbers) {
    _numbers = numbers;
    int answer = 0;
    
    for (bound = 1; bound <= numbers.size(); ++bound) {
        // bound = 현재 만들고자 하는 숫자의 길이
        dfs("");
        
        for (iter = result.begin(); iter != result.end(); ++iter) {
            cout << "소수 검사: " << *iter << '\n';
            if (isPrime(*iter)) ++answer;
        }
        result.clear();
    }
    
    return answer;
}