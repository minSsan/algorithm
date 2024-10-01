#include <iostream>
#include <string>

#define EMPTY '.'

using namespace std;

int n;
char parent[26];
char left_child[26];
char right_child[26];

string preorder(char root) {
    string result = {root};

    if (left_child[root-'A'] != EMPTY) {
        result.append(preorder(left_child[root-'A']));
    }
    if (right_child[root-'A'] != EMPTY) {
        result.append(preorder(right_child[root-'A']));
    }

    return result;
}

string inorder(char root) {
    string result = "";

    if (left_child[root-'A'] != EMPTY) {
        result.append(inorder(left_child[root-'A']));
    }
    result += root;
    if (right_child[root-'A'] != EMPTY) {
        result.append(inorder(right_child[root-'A']));
    }

    return result;
}

string postorder(char root) {
    string result = "";

    if (left_child[root-'A'] != EMPTY) {
        result.append(postorder(left_child[root-'A']));
    }
    if (right_child[root-'A'] != EMPTY) {
        result.append(postorder(right_child[root-'A']));
    }

    return result + root;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        parent[i] = EMPTY;
        left_child[i] = EMPTY;
        right_child[i] = EMPTY;
    }

    for (int i = 0; i < n; ++i) {
        char cur, lft, rgt;
        cin >> cur >> lft >> rgt;
        if (lft != EMPTY) {
            parent[lft-'A'] = cur;
            left_child[cur-'A'] = lft;
        }
        if (rgt != EMPTY) {
            parent[rgt-'A'] = cur;
            right_child[cur-'A'] = rgt;
        }
    }

    cout << preorder('A') << '\n' << inorder('A') << '\n' << postorder('A') << '\n';

    return 0;
}