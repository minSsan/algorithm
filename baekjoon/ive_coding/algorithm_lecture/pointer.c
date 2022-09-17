#include <stdio.h>
#include <stdlib.h>

void add(int* a) {
    (*a)++;
}

int main() {
    int a = 10;
    add(&a);
    printf("%d\n", a);
    return 0;
}