# 이진 검색 트리 (Binary Search Tree)

## `C++` STL

### set, multiset

> **이진 검색 트리** 자료구조로 **단일 값을 저장**할 때 사용한다. `O(logN)`  
> 중복을 허용할 경우에는 `multiset`, 그렇지 않은 경우에는 `set`을 사용한다.

- **_insert_**
  - @param - `추가할 값`
- **_erase_**  
   ⭐️ `multiset`의 경우 매칭되는 값을 **모두 삭제**한다.
  - @param - `삭제할 값` 또는 `iterator` _(👉🏻 [ multiset ] 하나의 값만 삭제하려면 iterator를 넘겨야 한다)_
  - @return - **삭제한 원소**의 바로 다음 iterator인 `next iterator` _(존재하지 않으면 `end iterator` 반환)_
- **_find_**
  - @param - `찾을 값`
  - @return - 찾는 원소의 `iterator` _(원소가 존재하지 않으면 `end iterator` 반환)_

```cpp
#include <iostream>
#include <set>

using namespace std;

multiset<int> tmp;

void print_tmp() {
    for (auto iter = tmp.begin(); iter != tmp.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << '\n';
}

int main() {
    tmp.insert(3);
    tmp.insert(3);
    tmp.insert(3);
    tmp.insert(3);
    tmp.insert(1);
    tmp.insert(5);
    tmp.insert(5);
    tmp.insert(2);
    tmp.insert(4);

    print_tmp(); // 1, 2, 3, 3, 3, 3, 4, 5, 5

    cout << distance(tmp.begin(), tmp.lower_bound(3)) << '\n'; // 2 (3이 처음 등장한 위치 - 시작 위치)

    auto range = tmp.equal_range(3);
    cout << distance(range.first, range.second) << '\n'; // 4

    // 중복하는 원소도 모두 삭제
    tmp.erase(3);
    print_tmp(); // 1, 2, 4, 5, 5

    // 하나의 원소만 삭제
    tmp.erase(tmp.find(5));
    print_tmp(); // 1, 2, 4, 5

    return 0;
}
```

### map

> **이진 검색 트리** 자료구조로 **key - value 쌍을 저장**할 때 사용한다. `O(logN)`  
> 키의 중복을 허용할 경우에는 `multimap`, 그렇지 않은 경우에는 `map`을 사용한다.

- **_삽입_**
  - insert 메소드를 사용할 수도 있지만, 딕셔너리처럼 `tmp[key] = value` 형태로 값을 삽입하는 것이 간편하다.
- **_erase_**  
  ⭐️ 마찬가지로 `multimap`의 경우 매칭되는 값을 **모두 삭제**한다.
  - @param - `삭제할 값` 또는 `iterator` _(👉🏻 [ multimap ] 하나의 값만 삭제하려면 iterator를 넘겨야 한다)_
  - @return - **삭제한 원소**의 바로 다음 iterator인 `next iterator` _(존재하지 않을 경우 `end iterator`를 반환)_
- **_find_**
  - @param - `찾을 값`
  - @return - 찾은 원소의 `iterator` _(존재하지 않을 경우 `end iterator`를 반환)_

```cpp
#include <iostream>
#include <string>
#include <map>

using namespace std;

map<string, int> tmp;

void print_tmp() {
    for (auto iter = tmp.begin(); iter != tmp.end(); ++iter) {
        cout << iter->first << ' ' << iter->second << '\n';
    }
}

int main() {
    tmp["a"] = 1;
    tmp["b"] = 2;
    tmp["c"] = 3;

    tmp.erase(tmp.find("b"));
    print_tmp(); // {"a", 1}, {"c", 3}

    return 0;
}
```

## `Java` Library

> 자바에서 이진 탐색 트리로 구현된 자료구조는 `TreeSet`, `TreeMap`이 있다.  
> 하지만 C++과 다르게 자바에서는 multiset, multimap과 같이 **중복 허용 BST는 제공하지 않는다.** _(필요한 경우 `TreeMap`의 value 값으로 개수를 저장할 수 있음 - `BOJ 7662` 자바코드 참고)_

### TreeSet

- **_add_**

  - @param - `추가할 값`

- **_remove_**

  - @param - `삭제할 값`

- **_contains_**

  - @param - 존재 여부를 `확인할 값`
  - @return - 값 존재 여부 _(Boolean)_

- **_first_**

  - @return - 정렬 기준으로 가장 앞에 있는 값

- **_last_**

  - @return - 정렬 기준으로 가장 마지막에 있는 값

- **_pollFirst_**  
   정렬 기준으로 가장 앞에 있는 값 삭제

- **_pollLast_**  
   정렬 기준으로 가장 마지막에 있는 값 삭제

- **_higher_**

  - @param - 비교 값
  - @return - 주어진 `값보다 큰 원소 중 가장 작은` 원소

- **_lower_**
  - @param - 비교 값
  - @return - 주어진 `값보다 작은 원소 중 가장 큰` 원소

### TreeMap

- **_put_**

  - @param - 추가할 `엔트리의 Key 값` _(이미 존재하는 key 값의 경우, value값이 수정)_
  - @param - 추가할 `엔트리의 Value 값`

- **_remove_**

  - @param - 삭제할 `엔트리의 Key 값`

- **_containsKey_**

  - @param - 존재 여부를 `확인할 키`
  - @return - 키 존재 여부 _(Boolean)_

- **_containsValue_**

  - @param - 존재 여부를 `확인할 값`
  - @return - 값 존재 여부 _(Boolean)_

- **_firstEntry_**

  - @return - **정렬 기준으로** 가장 앞에 있는 `Map.Entry<T, T>` 타입의 엔트리 객체

- **_lastEntry_**

  - @return - **정렬 기준으로** 가장 마지막에 있는 `Map.Entry<T, T>` 타입의 엔트리 객체

- **_remove_**

  - @param - 삭제할 `Entry의 Key 값`

- **_pollFirstEntry_**  
   정렬 기준으로 가장 앞에 있는 엔트리 삭제

- **_pollLastEntry_**  
   정렬 기준으로 가장 마지막에 있는 엔트리 삭제

- **_higherKey_**

  - @param - 비교 키 값
  - @return - 주어진 `키 값보다 큰 원소 중 가장 작은` 키 값

- **_lowerKey_**
  - @param - 비교 키 값
  - @return - 주어진 `값보다 작은 원소 중 가장 큰` 키 값

```java
import java.io.*;
import java.util.*;

public class Main {
    private static void printMap(Set<Map.Entry<Integer, String>> entrySet) {
        for (Map.Entry<Integer, String> entry : entrySet) {
            System.out.print("{ " + entry.getKey() + ", " + entry.getValue() + " }");
        }
        System.out.println();
    }

    public static void main(String[] args) {
        TreeMap<Integer, String> map = new TreeMap<>();

        map.put(1, "a"); // {1, "a"}
        map.put(2, "b"); // {1, "a"}, {2, "b"}
        map.put(1, "c"); // {1, "c"}, {2, "b"}
        map.put(4, "d"); // {1, "c"}, {2, "b"}, {4, "d"}
        printMap(map.entrySet());

        map.pollFirstEntry(); // {2, "b"}, {4, "d"}
        printMap(map.entrySet());

        map.pollLastEntry(); // {2, "b"}
        printMap(map.entrySet());
    }
}
```
