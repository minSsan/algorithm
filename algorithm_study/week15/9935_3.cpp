#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

int main() {
    string msg, explo;
    cin >> msg >> explo;

    vector<char> result;

    for (int i = 0; i < msg.size(); ++i) {
        result.push_back(msg[i]);

        if (result.size() >= explo.size()) {
            bool isbomb = true;

            int start = (int)result.size() - (int)explo.size();
            for (int j = 0; j < explo.size(); ++j) {
                if (explo[j] != result[start+j]) {
                    isbomb = false;
                }
            }

                
            if (isbomb) {
                for (int j = 0; j < explo.size(); ++j) {
                    result.pop_back();
                }
            }
        }
    }

    // ? mirkovnizCC44
    // ? C4

    if (result.size() > 0) {
        for (int i = 0; i < result.size(); ++i) {
            cout << result[i];
        }
        cout << '\n';
    } else {
        cout << "FRULA\n";
    }
    
    return 0;
}