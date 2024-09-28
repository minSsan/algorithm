#include <iostream>
#include <string>
#include <map>

using namespace std;

map<string, int> tmp;

void print_tmp() {
    for (auto iter = tmp.begin(); iter != tmp.end(); ++iter) {
        cout << iter->first << ' ' << iter->second << '\n';
    }
}

int main() {
    tmp["a"] = 1;
    tmp["b"] = 2;
    tmp["c"] = 3;

    tmp.erase(tmp.find("b"));
    print_tmp(); // {"a", 1}, {"c", 3}

    return 0;
}