#include <iostream>

using namespace std;

int num[10000001], pivot;

void quickSort(int i, int j) {
    int left = i;
    int right = j;

    if (left >= right) {
        return ;
    }

    pivot = num[(left + right) / 2];

    while (left < right) {
        while (num[left] < pivot) {
            left++;
        }
        while (num[right] > pivot) {
            right--;
        }

        swap(num[left], num[right]);
        left++;
        right--;
    }

    quickSort(0, (i + j) / 2 - 1);
    quickSort((i + j) / 2 + 1, j);
}

int main() {
    int n;
    cin >> n;

    int inputNum;
    
    for (int i = 0; i < n; ++i) {
        cin >> inputNum;
        num[i] = inputNum;
    }

    quickSort(0, n-1);

    for (int i = 0; i < n; ++i) {
        cout << num[i] << '\n';
    }

    return 0;
}