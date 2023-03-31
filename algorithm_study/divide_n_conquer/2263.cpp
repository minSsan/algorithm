#include <iostream>
#include <vector>

using namespace std;

// * 인오더를 나타내는 n개의 자연수가 주어지고, 그 다음 줄에는 같은 식으로 포스트오더가 주어진다.

int n; // ? 정점의 수
int inorder[100000]; // ? 인오더 순서
int post[100001]; // ? i가 포스트오더에서 몇 번째로 방문했는지
vector<int> preorder;

void divide(int start_idx, int end_idx) {
    if (start_idx > end_idx) return;

    if (start_idx == end_idx) {
        preorder.push_back(inorder[start_idx]);
        return ;
    }

    int pivot, max = 0;
    for (int i = start_idx; i <= end_idx; ++i) {
        if (post[inorder[i]] > max) {
            pivot = i;
            max = post[inorder[i]];
        }
    }
    preorder.push_back(inorder[pivot]);
    divide(start_idx, pivot-1);
    divide(pivot+1, end_idx);
}

int main() {
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> inorder[i];
    }
    for (int i = 0; i < n; ++i) {
        int input;
        cin >> input;
        post[input] = i;
    }

    divide(0, n-1);

    for (int i = 0; i < n; ++i) {
        cout << preorder[i] << ' ';
    }
    cout << '\n';

    return 0;
}