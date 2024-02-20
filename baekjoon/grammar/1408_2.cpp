#include <iostream>

using namespace std;

struct Time {
    int h;
    int m;
    int s;
};

int time_to_second(Time t) {
    return t.s + t.m * 60 + t.h * 3600;
}

int main() {
    Time start, end;

    scanf("%d:%d:%d", &start.h, &start.m, &start.s);
    scanf("%d:%d:%d", &end.h, &end.m, &end.s);

    int result;
    int end_s = time_to_second(end);
    int start_s = time_to_second(start);

    if (start_s > end_s) {
        result = end_s + (24 * 3600) - start_s;
    } else {
        result = end_s - start_s;
    }

    printf("%02d:%02d:%02d\n", result / 3600, (result % 3600) / 60, result % 60);

    return 0;
}