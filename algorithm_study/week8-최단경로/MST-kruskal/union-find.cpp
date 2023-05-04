#include <iostream>

#define SIZE 100000

using namespace std;

int parent[SIZE];

// 어느 그룹에 속하는지 찾는다
int find(int n) {
    // parent가 자기 자신과 다르다는 것은, 이전에 그룹으로 묶이면서 parent가 자신보다 작은 다른 원소로 설정되었다는 뜻
    // 따라서 자신보다 작은 원소의 부모를 확인한다.
    if (parent[n] != n) {
        return find(parent[n]);
    }
    return n;
}

// ? parent = [1, 2, 3, 4]
// ? parent = [1, 2, 3, 3] <- parent[4] = parent[3]
// ? parent = [1, 1, 3, 3] <- parent[2] = parent[1]
// ? parent = [1, 1, 1, 3] <- parent[3] = parent[2]
// ? 3-4(2), 1-2(3), 2-3(4)
// ? {3, 4, 1, 2}
// 두 숫자를 같은 그룹으로 묶을 때, 둘 중 더 작은 부모를 부모로 설정한다.
void _union(int a, int b) {
    int a_parent = find(a);
    int b_parent = find(b);
    // a의 parent가 더 작은 경우, b의 parent의 부모를 a의 parent로 설정해야 한다. (b의 parent를 바꾸는 것 x)
    // -> 둘 중 더 작은 것을 부모로 설정. a_parent는 그대로 자기 자신을 부모로 갖는다.
    if (a_parent < b_parent) {
        parent[b_parent] = a_parent;
    } else { // -> b_parent는 그대로 자기 자신을 부모로 갖고, a_parent는 b_parent를 부모로 갖는다.
        parent[a_parent] = b_parent;
    }
}

int main() {
    // ? parent 정보 초기화 - 처음에는 parent는 자기 자신이 된다.
    for (int i = 0; i < SIZE; ++i) {
        parent[i] = i;
    }

    return 0;
}