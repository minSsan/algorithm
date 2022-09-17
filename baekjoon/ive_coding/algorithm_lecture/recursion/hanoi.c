#include <stdio.h>

int hanoi(int n) {
    if (n == 1) return 1;
    return 2 * hanoi(n-1) + 1;
}

int main() {
    printf("%d\n", hanoi(3)); // 7
    return 0;
}