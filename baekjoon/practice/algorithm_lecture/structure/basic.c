#include <stdio.h>

//? 구조체
struct st {
    char s[100];
    int m;
    int k;
    int e;
};

int main() {
    struct st s1; //? s1 이라는 st 구조체 생성
    scanf("%s %d %d %d", s1.s, &s1.m, &s1.k, &s1.e);
    printf("%s %d %d %d\n", s1.s, s1.m, s1.k, s1.e);
    return 0;
}