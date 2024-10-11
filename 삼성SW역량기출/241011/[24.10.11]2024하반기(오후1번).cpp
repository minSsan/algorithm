#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct santa {
	int r;
	int c;
	int num;
	int score;
	bool falied;
	int comma;
};

int n, m, p, c, d;

pair<int, int> deer_pos;
int grid[51][51];
santa santa_info[31];

int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};

void print_grid() {
	cout << "==============\n";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << grid[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << "==============\n";
}

void print_santa_info() {
	cout << "======기절, 점수, 실패=======\n";
	for (int i = 1; i <= p; ++i) {
		santa s = santa_info[i];
		cout << "[ " << s.num << " ]	" << s.comma << ", " << s.score << ", " << s.falied << '\n';
	}
	cout << "==========================\n";
}

//? santa_info를 기반으로 grid 배열을 업데이트
void set_grid() {
	//* 1. 초기화
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			grid[i][j] = 0;
		}
	}

	//* 2. 값 채우기
	for (int i = 1; i <= p; ++i) {
		santa s = santa_info[i];
		if (!s.falied) grid[s.r][s.c] = s.num;
	}
}

void update_comma() {
	for (int i = 1; i <= p; ++i) {
		santa s = santa_info[i];
		if (s.comma > 0) santa_info[s.num].comma--;
	}
}

bool is_valid_pos(int r, int c) {
	return r >= 0 && r < n && c >= 0 && c < n;
}

bool is_deer_pos(int r, int c) {
	return r == deer_pos.first && c == deer_pos.second;
}

bool is_santa_pos(int r, int c) {
	return grid[r][c] > 0;
}

int get_distance(int r1, int r2, int c1, int c2) {
	int a = (r1 - r2) * (r1 - r2);
	int b = (c1 - c2) * (c1 - c2);
	return a + b;
}

bool is_over() {
	for (int i = 1; i <= p; ++i) {
		if (!santa_info[i].falied) return false;
	}
	return true;
}

void increase_score() {
	for (int i = 1; i <= p; ++i) {
		if (!santa_info[i].falied) santa_info[i].score++;
	}
}

//? 우선순위가 더 높은 산타를 정렬
bool compare_priority_santa(santa a, santa b) {
	if (a.r != b.r) return a.r > b.r;
	return a.c > b.c;
}

//? 현재 루돌프와 가장 가까운 산타를 찾는다
santa find_near_santa() {
	int deer_row = deer_pos.first, deer_col = deer_pos.second;
	int min_dist = 100000000;
	vector<santa> coord;
	for (int i = 1; i <= p; ++i) {
		//* 탈락한 산타는 후보에서 제외한다.
		if (santa_info[i].falied) continue;
		//* i번 산타와 루돌프 사이의 거리
		int dist = get_distance(santa_info[i].r, deer_row, santa_info[i].c, deer_col);
		if (dist < min_dist) {
			coord.clear();
			coord.push_back(santa_info[i]);
			min_dist = dist;
		} else if (dist == min_dist) {
			coord.push_back(santa_info[i]);
		}
	}
	sort(coord.begin(), coord.end(), compare_priority_santa);
	return coord[0];
}

//? r, c 위치에서부터 dir 방향으로 밀려남 (상호작용)
void interaction(int r, int c, int dir) {
	int row = r, col = c;

	//* 1. 밀어낼 산타 목록
	vector<santa> santa_coord;
	santa_coord.push_back(santa_info[grid[r][c]]);
	while (is_valid_pos(row + dr[dir], col + dc[dir])) {
		row += dr[dir];
		col += dc[dir];
		if (grid[row][col] == 0) break;
		santa_coord.push_back(santa_info[grid[row][col]]);
	}

	//* 2. 산타 밀어내기
	for (santa s : santa_coord) {
		int next_r = s.r + dr[dir];
		int next_c = s.c + dc[dir];
		// 바깥으로 밀려난 경우
		if (!is_valid_pos(next_r, next_c)) {
			santa_info[s.num].falied = true;
			continue;
		}
		santa_info[s.num].r = next_r;
		santa_info[s.num].c = next_c;
	}

	//* 3. 변경사항 반영
	set_grid();
}

//? 루돌프를 움직이는 함수
void move_deer() {
	//* 1. 목표 산타 찾기
	santa target = find_near_santa();
	// cout << "루돌프의 목표는 " << target.num << "\n";

	//* 2. 방향 정하기
	int dir;
	int min_dist = 100000000;
	for (int i = 0; i < 8; ++i) {
		int next_row = deer_pos.first + dr[i];
		int next_col = deer_pos.second + dc[i];
		if (is_valid_pos(next_row, next_col)) {
			//? 목표 산타와 해당 방향으로 이동했을 때의 위치 사이 거리
			int dist = get_distance(next_row, target.r, next_col, target.c);
			if (dist < min_dist) {
				min_dist = dist;
				dir = i;
			}
		}
	}
	// cout << "루돌프의 방향은 " << dir << '\n';

	//* 3. 이동하기
	int next_row = deer_pos.first + dr[dir], next_col = deer_pos.second + dc[dir];
	//? 3-1. 산타가 존재하는 경우
	if (is_santa_pos(next_row, next_col)) {
		//? 1. 점수 획득 & 기절
		int santa_num = grid[next_row][next_col];
		santa_info[santa_num].score += c;
		santa_info[santa_num].comma = 2;


		//? 2. 루돌프 이동 방향으로 c칸 밀린다.
		int next_santa_row = next_row + dr[dir] * c;
		int next_santa_col = next_col + dc[dir] * c;

		// cout << santa_num << " 번 산타를 " << next_santa_row << ", " << next_santa_col << " 로 밀어냅니다.\n";
		
		//? 3-1. 범위를 벗어나지 않은 경우
		if (is_valid_pos(next_santa_row, next_santa_col)) {
			// 밀린 위치에 다른 산타가 존재하는 경우
			if (is_santa_pos(next_santa_row, next_santa_col)
					&& grid[next_santa_row][next_santa_col] != santa_num) {
				// 상호작용
				interaction(next_santa_row, next_santa_col, dir);
			}
			//? 밀린 산타의 위치 옮기기
			santa_info[santa_num].r = next_santa_row;
			santa_info[santa_num].c = next_santa_col;
			// cout << "밀린 산타의 갱신 위치는 " << next_santa_row << ", " << next_santa_col << '\n';
		}
		//? 3-2. 밀린 위치가 범위에서 벗어난 경우
		else {
			santa_info[santa_num].falied = true;
		}
	}
	// 변경사항 반영
	set_grid();
	//* 루돌프 위치 업데이트
	deer_pos.first = next_row; deer_pos.second = next_col;
	// cout << "루돌프의 새로운 위치는 " << deer_pos.first << ", " << deer_pos.second << '\n';
}

void move_santa(int num) {
	santa cur_santa = santa_info[num];
	int santa_row = cur_santa.r, santa_col = cur_santa.c;
	
	//* 1. 이동방향 결정
	int cur_dist = get_distance(santa_row, deer_pos.first, santa_col, deer_pos.second);
	int min_dist = cur_dist;
	int dir;
	for (int i = 0; i < 8; i += 2) {
		int coord_row = santa_row + dr[i];
		int coord_col = santa_col + dc[i];
		//? 범위 내의 위치이면서 산타가 존재하지 않는 위치일 경우
		if (is_valid_pos(coord_row, coord_col) && !is_santa_pos(coord_row, coord_col)) {
			//? 후보 목적지와 루돌프 사이의 거리 구하기
			int dist = get_distance(coord_row, deer_pos.first, coord_col, deer_pos.second);
			if (dist < min_dist) {
				dir = i;
				min_dist = dist;
			}
		}
	}

	// cout << num << " 번 산타의 이동방향: " << dir << '\n';

	//* 더이상 갈 수 있는 길이 없거나, 더 가까운 방향으로 가지 못 하는 경우, 이동하지 않는다.
	if (min_dist >= cur_dist) {
		return ;
	}

	//* 2. 이동방향으로 이동
	int next_row = santa_row + dr[dir];
	int next_col = santa_col + dc[dir];

	//* 2-1. 목적지에 루돌프가 있는 경우(충돌)
	if (is_deer_pos(next_row, next_col)) {
		//? 1. 점수 기록 & 기절
		santa_info[num].score += d;
		santa_info[num].comma = 2;

		//? 2. 반대방향으로 d만큼 밀림
		int push_dir = (dir + 4) % 8;
		int push_row = next_row + dr[push_dir] * d;
		int push_col = next_col + dc[push_dir] * d;

		//? 3-1. 범위를 벗어나지 않은 경우
		if (is_valid_pos(push_row, push_col)) {
			// 밀린 위치에 다른 산타가 존재하는 경우
			if (is_santa_pos(push_row, push_col) && santa_info[grid[push_row][push_col]].num != num) {
				// 상호작용
				interaction(push_row, push_col, push_dir);
				// cout << num << " 번 산타가 " << push_row << ", " << push_col << " 로 이동하는 과정에서 상호작용 발생" << '\n';
			}
			//? 밀린 산타의 위치 옮기기
			santa_info[num].r = push_row;
			santa_info[num].c = push_col;
		}
		//? 3-2. 밀린 위치가 범위에서 벗어난 경우
		else {
			santa_info[num].falied = true;
		}		
	} 
	//* 2-2. 목적지에 아무것도 없는 경우
	else {
		santa_info[num].r = next_row;
		santa_info[num].c = next_col;
	}
	// 변경사항 반영
	set_grid();
}

int main() {
	cin >> n >> m >> p >> c >> d;
	cin >> deer_pos.first >> deer_pos.second;
	--deer_pos.first; --deer_pos.second;
	for (int i = 0; i < p; ++i) {
		int r, c, num;
		cin >> num >> r >> c;
		grid[r-1][c-1] = num;
		santa_info[num] = {r-1, c-1, num, 0, 0, 0};
	}

	while (m--) {
		if (is_over()) break;

		//* 1. 루돌프 움직임
		move_deer();

		//* 2. 1 ~ p번 산타 움직임 (기절 | 탈락 제외)
		for (int i = 1; i <= p; ++i) {
			if (santa_info[i].comma == 0 && !santa_info[i].falied) {
				move_santa(i);
				// cout << i << " 번 산타 이동 후\n";
				// print_grid();
			}
		}

		// cout << deer_pos.first << ", " << deer_pos.second << '\n';
		// print_grid();
		//* 3. 기절 상태 변경 및 생존 점수 추가
		update_comma();
		increase_score();
	}

	for (int i = 1; i <= p; ++i) {
		cout << santa_info[i].score << ' ';
	}
	cout << '\n';

	return 0;
}