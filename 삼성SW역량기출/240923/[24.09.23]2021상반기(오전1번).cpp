#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct prefer {
    int like_cnt;   // 좋아하는 학생 수
    int empty_cnt;  // 비어있는 자리 수
    int row;        // 행
    int col;        // 열
};

vector<prefer> coord; // 현재 학생의 선호도 배열

map<int, vector<int>> likes_list; // i번 학생이 좋아하는 학생 목록
vector<int> students; // 배치 순서

int n;
int seat[20][20]; // 좌석 배치도
int satisfy[5]; // 만족도

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void print_seat() {
    cout << "[ seat ]\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << seat[i][j] << ' ';
        }
        cout << '\n';
    }
}

bool compare(prefer a, prefer b) {
    if (a.like_cnt != b.like_cnt) return a.like_cnt > b.like_cnt;
    if (a.empty_cnt != b.empty_cnt) return a.empty_cnt > b.empty_cnt;
    if (a.row != b.row) return a.row < b.row;
    return a.col < b.col;
}

bool is_valid(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < n;
}

//? likes 배열에 num번 학생이 존재하는지 확인
bool exist_like(int num, vector<int> likes) {
    for (int like : likes) {
        if (like == num) return true;
    }
    return false;
}

//? num 학생의 seat[r][c] 자리에 대한 선호 정보 가져오기
prefer get_prefer(int r, int c, int num) {
    prefer result = {0, 0, r, c};
    for (int i = 0; i < 4; ++i) {
        int row = r + dr[i], col = c + dc[i];
        if (is_valid(row, col)) {
            if (seat[row][col] == 0) result.empty_cnt++;
            else if (exist_like(seat[row][col], likes_list[num])) result.like_cnt++;
        }
    }
    return result;
}

void define_seat(int num) {
    //* 선호 자리 찾기
    coord.clear();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            //? 비어있는 자리라면 선호도 조사를 진행한다.
            if (seat[i][j] == 0) coord.push_back(get_prefer(i, j, num));
        }
    }
    sort(coord.begin(), coord.end(), compare);
    
    //* coord[0] 원소의 row, col 위치로 자리 정하기
    int row = coord[0].row; int col = coord[0].col;
    seat[row][col] = num;
}

void research_satisfy() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int score = 0;

            int num = seat[i][j];
            vector<int> likes = likes_list[num];

            for (int d = 0; d < 4; ++d) {
                int next_r = i + dr[d]; int next_c = j + dc[d];
                if (is_valid(next_r, next_c) && exist_like(seat[next_r][next_c], likes)) {
                    score++;
                }
            }

            satisfy[score]++;
        }
    }
}

int get_result() {
    return satisfy[1] + 10 * satisfy[2] + 100 * satisfy[3] + 1000 * satisfy[4];
}

int main() {
    cin >> n;
    for (int i = 0; i < n*n; ++i) {
        int num;
        cin >> num; // 학생 번호 입력
        students.push_back(num);
        
        vector<int> temp(4);
        for (int j = 0; j < 4; ++j) {
            cin >> temp[j]; // num번 학생이 선호하는 학생 목록 입력
        }
        likes_list[num] = temp;
    }

    //* 1. 자리 정하기
    for (int student_num : students) {
        define_seat(student_num);
    }

    //* 2. 만족도 조사하기
    research_satisfy();

    cout << get_result() << '\n';

    return 0;
}