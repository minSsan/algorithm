#include <iostream>
#include <deque>

using namespace std;

int n, k;
int position[200001]; // n번 로봇이 있는 벨트 번호
int robot_num;

struct belt_info {
    int num;    // 벨트의 번호
    int robot;  // 올려져 있는 로봇의 번호
    int a;      // 내구도
};

deque<belt_info> belt;

void print_belt() {
    cout << "=== { 벨트 번호, 로봇 번호, 내구도 } 순 ===\n";
    for (int i = 0; i < n; ++i) {
        cout << "{ " << belt[i].num << ", " << belt[i].robot << ", " << belt[i].a << " }";
    }
    cout << '\n';
    for (int i = 2*n-1; i >= n; --i) {
        cout << "{ " << belt[i].num << ", " << belt[i].robot << ", " << belt[i].a << " }";
    }
    cout << '\n';
    cout << '\n';
}

// 내리는 위치에 있는 로봇을 없앤다.
void take_off_robot() {
    belt_info* info = &belt[n-1];
    if (info->robot != 0) {
        position[info->robot] = 0;
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

// 벨트의 position 위치에 있는 로봇을 한 칸 옮기는 함수
void move_robot(int position_num) {
    for (int i = 0; i < belt.size(); ++i) {
        if (belt[i].num == position_num) {
            belt_info* current_info = &belt[i];
            belt_info* next_info = &belt[(i+1)%(2*n)];

            if (next_info->a > 0 && next_info->robot == 0) {
                next_info->robot = current_info->robot;
                --(next_info->a);
                position[current_info->robot] = next_info->num;
                current_info->robot = 0;
            }
            break;
        }
    }
    take_off_robot();
}

// 로봇을 한 칸씩 움직인다.
void rotate_robot() {
    for (int i = 1; i < robot_num; ++i) {
        if (position[i] != 0) { // i번 로봇이 벨트 위에 있다면,
            move_robot(position[i]);
        }
    }
}

// 올리는 위치에 로봇을 올린다.
void add_robot() {
    if (belt[0].a > 0 && belt[0].robot == 0) {
        --belt[0].a;
        position[robot_num] = belt[0].num;
        belt[0].robot = robot_num++;
    }
}

bool is_done() {
    int cnt = 0;
    for (belt_info info : belt) {
        if (info.a == 0) ++cnt;
    }
    return cnt >= k;
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= 2*n; ++i) {
        int input_v;
        cin >> input_v;
        belt.push_back({i, 0, input_v});
    }

    robot_num = 1;
    int step = 1;

    while (!is_done()) {
        //* 1. 회전 방향으로 로봇과 함께 벨트 회전
        rotate_belt();
        // cout << "==== 벨트 회전 이후\n";
        // print_belt();
        // cout << "================\n\n";

        //* 2. 먼저 올라간 순서대로 로봇을 이동방향으로 한 칸씩 이동
        rotate_robot();
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