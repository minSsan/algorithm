#include <iostream>
#include <deque>
#include <queue>
#include <vector>

using namespace std;

int n, k;
int robot_num;
int zero_a_cnt;

struct belt_info {
    int robot;  // 올려져 있는 로봇의 번호
    int a;      // 내구도
};

deque<belt_info> belt;

void print_belt() {
    cout << "=== { 로봇 번호, 내구도 } 순 ===\n";
    for (int i = 0; i < n; ++i) {
        cout << "{ " << belt[i].robot << ", " << belt[i].a << " }";
    }
    cout << '\n';
    for (int i = 2*n-1; i >= n; --i) {
        cout << "{ " << belt[i].robot << ", " << belt[i].a << " }";
    }
    cout << '\n';
    cout << '\n';
}

// 내리는 위치에 있는 로봇을 없앤다.
void take_off_robot() {
    belt_info* info = &belt[n-1];
    if (info->robot != 0) {
        info->robot = 0;
    }
}

// 벨트를 회전시킨다.
void rotate_belt() {
    //* 1. 회전
    belt_info end_slot = belt.back();
    belt.pop_back();
    belt.push_front(end_slot);

    //* 2. 회전 후, 내리는 위치에 있는 로봇 제거
    take_off_robot();
}

// 벨트의 index 위치에 있는 로봇을 한 칸 옮기는 함수
void move_robot(int index) {
    belt_info* current_info = &belt[index];
    if (current_info->robot == 0) return;
    belt_info* next_info = &belt[(index+1)%(2*n)];

    if (current_info->robot > 0 && next_info->a > 0 && next_info->robot == 0) {
        next_info->robot = current_info->robot;
        --next_info->a;
        if (next_info->a == 0) zero_a_cnt++;
        current_info->robot = 0;
    }
    
    take_off_robot();
}

// 로봇을 한 칸씩 움직인다.
void rotate_robot() {
    for (int i = n-2; i >= 0; --i) {
        move_robot(i);
    }
}

// 올리는 위치에 로봇을 올린다.
void add_robot() {
    if (belt[0].a > 0 && belt[0].robot == 0) {
        --belt[0].a;
        if (belt[0].a == 0) zero_a_cnt++;
        belt[0].robot = robot_num++;
    }
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= 2*n; ++i) {
        int input_v;
        cin >> input_v;
        belt.push_back({0, input_v});
    }

    robot_num = 1;
    int step = 1;

    while (zero_a_cnt < k) {
        //* 1. 회전 방향으로 로봇과 함께 벨트 회전
        rotate_belt();
        // cout << "==== 벨트 회전 이후\n";
        // print_belt();
        // cout << "================\n\n";

        //* 2. 먼저 올라간 순서대로 로봇을 이동방향으로 한 칸씩 이동
        rotate_robot(); // 4만
        // cout << "==== 로봇 회전 이후\n";
        // print_belt();
        // cout << "================\n\n";

        //* 3. 올리는 위치에 로봇 올리기
        add_robot();
        // cout << "==== 로봇 추가 이후\n";
        // print_belt();
        // cout << "================\n\n";
        ++step;
    }

    cout << step - 1 << '\n';

    return 0;
}