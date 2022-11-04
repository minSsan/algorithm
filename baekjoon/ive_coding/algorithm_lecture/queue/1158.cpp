#include <iostream>
#include <queue>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    
    queue<int> people;
    for (int i = 1; i <= n; ++i) {
        people.push(i);
    }

    cout << '<';
    while (people.size() > 1) {
        for (int i = 0; i < k - 1; ++i) {
            people.push(people.front());
            people.pop();
        }
        cout << people.front() << ", ";
        people.pop();
    }
    cout << people.front() << ">\n";

    return 0;
}