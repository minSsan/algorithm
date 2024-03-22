## vector에서 특정 값 찾기

### find 함수

`algorithm` 라이브러리의 find 함수를 사용하면 벡터 내의 특정 값 존재 여부를 확인할 수 있다.

```
find(iter 시작부분, iter 끝부분, 찾는 값)
```

```cpp
#include <vector>
#include <algorithm>

int main() {
    vector<int> v;

    v.push_back(1);
    v.push_back(2);

    // 원소의 iterator 값을 리턴한다.
    auto iter = find(v.begin(), v.end(), 1);

    int index = iter - v.begin();
    cout << "1의 인덱스 값: " << index << '\n' ;

    if (iter != v.end()) { // 값이 존재하는 경우
        v.erase(iter);
    }

    return 0;
}

```

이를 활용하면 벡터 내에 저장된 특정 값을 삭제할 수도 있다.

```
v.erase(삭제하려는 원소의 iter 값)
```
