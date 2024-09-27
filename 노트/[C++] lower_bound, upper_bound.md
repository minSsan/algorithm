⭐️ 저장된 값이 `오름차순`으로 정렬된 상태일 때, 원하는 값을 정상적으로 찾을 수 있다.

- _(참고)_ **이진 검색 트리 STL**(`set`, `multiset`, `map`)에 해당 메서드가 내장되어 있음.

# lower_bound

> 찾으려는 key 값보다 `크거나 같은 숫자`가 **처음 등장하는 위치**를 반환한다.

#### std::lower_bound

```cpp
#include <iostream>

using namespace std;

int main() {
    int arr[6] = {1, 2, 3, 4, 5, 6};
    auto iter = lower_bound(arr, arr+6, 6); // 6보다 크거나 같은 숫자가 처음 등장하는 위치
    cout << "first '6' index is [ " << iter - arr << " ]\n"; // 5
    return 0;
}
```

# upper_bound

> 찾으려는 key 값보다 `큰 숫자`가 **처음 등장하는 위치**를 반환한다.

#### std::upper_bound

```cpp
#include <iostream>

using namespace std;

int main() {
    int arr[6] = {1, 2, 3, 4, 5, 6};
    auto iter = upper_bound(arr, arr+6, 3); // 3보다 큰 숫자가 처음 등장하는 위치
    cout << "first bigger than '3' index is [ " << iter - arr << " ]\n"; // 3
    return 0;
}
```

### 활용 문제

1. **값이 모두 정렬된 상태**에서 `특정 범위`에 있는 숫자가 몇 개 존재하는지 찾고 싶을 때

2. **값이 모두 정렬된 상태**에서 `특정 숫자`가 몇 개 존재하는지 찾고 싶을 때
