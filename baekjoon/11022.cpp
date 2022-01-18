#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, A, B;
    cin >> T;

    for(int i = 0; i < T; ++i) {
        cin >> A >> B;
        cout << "Case #" << to_string(i+1) << ": " << to_string(A) << " + " << to_string(B) << " = " << to_string(A+B) << '\n'; 
    }

    return 0;
}