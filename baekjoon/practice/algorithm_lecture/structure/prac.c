#include <stdio.h>

struct st {
    char s[100];
    int m;
    // int k;
    // int e;
};

int main() {
    struct st arr[100];
    int n;

    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%s %d", &arr[i].s[0], &arr[i].m);
    }

    // 수학 점수 높은 순 정렬
    char tmp_s[100];
    int tmp_m;

    for(int k = 0; k < n-1; k++){
        for (int i = 0; i < n - 1; ++i) {
            if (arr[i].m < arr[i+1].m) {
                for (int j = 0; j < 100; ++j) {
                    tmp_s[j] = arr[i].s[j];
                    arr[i].s[j] = arr[i+1].s[j];
                    arr[i+1].s[j] = tmp_s[j];
                }
                tmp_m = arr[i].m;
                
                arr[i].m = arr[i+1].m;
                
                arr[i+1].m = tmp_m;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        printf("%s %d\n", arr[i].s, arr[i].m);
    }

    return 0;
}