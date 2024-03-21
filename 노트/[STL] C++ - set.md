# C++에서 set 사용하기

**중복값을 허용하지 않고 값을 저장해야 하는 경우**, 대부분 집합을 사용하게 된다. 원래는 `set STL`을 사용한 경험이 없어서 직접 중복 여부를 체크하는 식으로 구현했는데, 실제 시험장에서 이렇게 구현하면 시간 낭비가 심할 것 같아서 이번 기회에 해당 STL을 학습하게 되었다.

[관련 문제 링크](https://school.programmers.co.kr/learn/courses/30/lessons/42839)

## 설명

연관 컨테이너의 한 종류로, **이진트리**로 구현되어 있어 _저장 순서를 지정할 수 없다._ 이러한 특징 때문에 데이터를 **항상 오름차순**으로 저장한다.

#### > 연관 컨테이너?

`key-value` 쌍으로 데이터를 저장하는 컨테이너를 의미하고, 종류는 아래와 같다.

```text
set
multiset
map
multimap
```

> 키 값으로 데이터에 접근하므로 **접근 속도가 빠르다**는 특징이 있음 (vector보다 빠른 속도로 활용 가능)

그 중에서 이번에 사용한 `set는` **key의 중복값을 허용하지 않고**, `multiset의` 경우 **key의 중복값을 허용**한다.

### 선언하기

```cpp
set<int> s;
```

### 값 삽입/삭제하기

```cpp
s.insert(5);    // 원소 5 삽입. 리턴 값은 <삽입 위치 iter값, bool>
s.erase(5);     // 원소 5 삭제
s.clear();      // 전체 원소 삭제
```

> 여기서 값 삽입에 실패하면 리턴 pair의 second 값은 false가 된다.

### 값 출력하기

값을 출력하는 경우에는 `iterator`를 이용해야 한다.

```cpp
#include <set>
#include <iostream>

using namespace std;

int main() {
    set<int> s;
    set<int>::iterator iter;

    s.insert(10);
    s.insert(20);
    s.insert(30);

    for (iter = s.begin(); iter != s.end(); ++iter) {
        cout << *iter << ' '; // 10 20 30
    }
}
```

### 값 확인하기

```cpp
s.find(5);  // 원소 5의 iter 값 리턴, 없으면 s.end() 리턴
s.empty();
s.size();   // 저장된 원소의 수
```
