#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    cin.ignore();
    // 버퍼에 담긴 '\n' 무시 (-> getline에서는 '\n'에 대한 버퍼를 남기지 않기 때문)

    stack<char> word_stack;

    while(T--) {
        string sentence;
        getline(cin, sentence);
        sentence += '\n';

        for(char word : sentence) {
            if(word == ' ' || word == '\n') {
                while(!word_stack.empty()) {
                    cout << word_stack.top();
                    word_stack.pop();
                }
                cout << word;
            }
            else {
                word_stack.push(word);
            }
        }
    }

    return 0;
}
