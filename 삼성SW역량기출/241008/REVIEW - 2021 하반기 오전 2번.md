## 문제 정보

> 삼성 SW 역량 테스트 - 2021년 하반기 오전 2번  
> [백준 23289번](https://www.acmicpc.net/problem/23289)  
> ⏰ 3시간 15분  
> 시뮬레이션, 구현

## 구현 과정

- 문제 필기 + 로직 설계 (약 1시간)
- 코드 작성 (약 1시간 45분)
- 문제점 해결 (약 30분)

## 문제가 된 부분

- **_벽이 있는 칸 검사_**

  - **_다음 칸으로 넘어가기 전에_** 현재 칸과 다음 칸 사이에 벽이 존재하는지 확인해야 한다.
  - 하지만 첫 풀이 코드에서는 **_다음 칸으로 이미 넘어간 후에_**, 다다음 칸과의 벽 존재 여부를 검사했음.

    #### ✅ 올바른 코드

    ```cpp
    for (int i = 0; i < 3; ++i) {
        bool flag = true;
        int next_row = row, next_col = col;
        for (int j = 0; j < 2; ++j) {
            // 이동 경로 중에 벽을 만나는지 검사 -> flag = false
            if (is_exist_wall(next_row, next_col, next_row+dr[info-1][i][j], next_col+dc[info-1][i][j])) {
                flag = false;
                break;
            }

            next_row += dr[info - 1][i][j];
            next_col += dc[info - 1][i][j];

            if (!is_valid_pos(next_row, next_col)) {
                flag = false;
                break;
            }
        }
        if (flag && !visited[next_row][next_col]) {
            q.push({next_row, next_col, tmp-1});
            visited[next_row][next_col] = true;
        }
    }
    ```

    #### ❌ 틀린 코드

    ```cpp
    for (int i = 0; i < 3; ++i) {
        bool flag = true;
        int next_row = row, next_col = col;
        for (int j = 0; j < 2; ++j) {
            next_row += dr[info - 1][i][j];
            next_col += dc[info - 1][i][j];

            if (!is_valid_pos(next_row, next_col)) {
                flag = false;
                break;
            }

            // 이동 경로 중에 벽을 만나는지 검사 -> flag = false
            if (is_exist_wall(next_row, next_col, next_row+dr[info-1][i][j], next_col+dc[info-1][i][j])) {
                flag = false;
                break;
            }
        }
        if (flag && !visited[next_row][next_col]) {
            q.push({next_row, next_col, tmp-1});
            visited[next_row][next_col] = true;
        }
    }
    ```

## 개선된 점

- `dr`, `dc` 활용이 이전보다 개선된 것을 느낌

  - 예전에 _(정확히 무슨 문제인지는 모르겠지만)_ `if 문`으로 죄다 분기해서 처리했던걸로 기억하는데, 이번에는 `dr`, `dc` 배열을 `(온풍기 방향, 이동 방향)`에 따라서 미리 설계를 해둬서, 이전보다 코드가 훨씬 깔끔해짐

- 관리해야할 정보가 비교적 복잡했는데, 이 부분들을 **미리 모두 설계한 후에 코드를 작성한 점**
  - 특히, **모든 위치에 대해서 `상/하/좌/우`에 벽이 존재하는지** 저장하기 위해 3차원 배열로 설계한 것

## 아쉬운 점

- 벽을 검사하는 부분

  - 벽 존재 여부를 검사하는 로직(`is_exist_wall`)의 기준은 **"현재 위치"와 "다음 위치" 사이**였는데, 해당 로직을 호출하는 부분에서는 **"다음 위치"와 "다다음 위치" 사이를 검사**하게끔 설계한 것.

  👉🏻 코드를 작성할 때 로직에 대한 검증을 더 꼼꼼하게 할 필요가 있다.
