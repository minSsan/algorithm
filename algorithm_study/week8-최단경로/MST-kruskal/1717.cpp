#include <iostream>

using namespace std;

int parent[1000001];

int find(int n) {
    // ? 이 방법은 시간초과 발생. parent를 찾은 결과를 기록해두지 않기 때문에, find를 호출할 때마다 비효율적으로 parent를 찾아야 함
    // if (parent[n] != n) return find(parent[n]);
    // ? parent 배열을 갱신하여 시간 단축
    if (parent[n] != n) return parent[n] = find(parent[n]);
    return n;
}

void _union(int a, int b) {
    a = find(a);
    b = find(b);

    if (a < b) {
        parent[b] = a;
    } else {
        parent[a] = b;
    }
}

bool is_same_group(int a, int b) {
    if (find(a) == find(b)) return true;
    return false;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i <= n; ++i) {
        parent[i] = i;
    }

    int op, a, b;
    for (int i = 0; i < m; ++i) {
        cin >> op >> a >> b;
        // Union
        if (op == 0) {
            if (!is_same_group(a, b)) _union(a, b);
        } 
        else if (op == 1) {
            if (is_same_group(a, b)) cout << "YES\n";
            else cout << "NO\n";
        }
    }

    return 0;
}