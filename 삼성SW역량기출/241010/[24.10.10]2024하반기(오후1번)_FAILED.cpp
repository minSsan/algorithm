#include <iostream>
#include <queue>
#include <cmath>
#include <algorithm>
#include <vector>

#define DEER -1

using namespace std;

int n, m, p, c, d;

pair<int, int> deer_pos;
int deer_dir;
int santa_dir; // 현재 이동중인 산타의 이동방향
int grid[50][50];
bool visited[50][50];

int score[31];
bool failed[31];
int comma[31];

int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};

void print_grid() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << grid[i][j] << ' ';
		}
		cout << '\n';
	}
}

void init_visited() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			visited[i][j] = false;
		}
	}
}

bool is_over() {
	for (int i = 1; i <= p; ++i) {
		if (!failed[i]) return false;
	}
	return true;
}

bool is_exist_santa(int row, int col) {
	return grid[row][col] > 0;
}

bool is_exist_deer(int row, int col) {
	return row == deer_pos.first && col == deer_pos.second;
}

int get_distance(pair<int, int> start, pair<int, int> end) {
	int a = pow(abs(start.first - end.first), 2);
	int b = pow(abs(start.second - end.second), 2);
	return a + b;
}

void increase_score() {
	for (int i = 1; i <= p; ++i) {
		if (!failed[i]) score[i]++;
	}
}

void update_comma() {
	for (int i = 1; i <= p; ++i) {
		if (comma[i] > 0) comma[i]--;
	}
}

bool is_valid_pos(int row, int col) {
	return row >= 0 && row < n && col >= 0 && col < n;
}

bool compare_santa_pos(pair<int, int> a, pair<int, int> b) {
	if (a.first != b.first) return a.first > b.first;
	return a.second > b.second;
}

pair<int, int> get_santa_pos(int num) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (grid[i][j] == num) return { i, j };
		}
	}
	return { -1, -1 };
}

// num번 산타를 실패처리
void go_out_santa(int num) {
	pair<int, int> pos = get_santa_pos(num);
	failed[num] = true;
	grid[pos.first][pos.second] = 0;
}

pair<int, int> get_next_deer_pos() {
	init_visited();

	queue<pair<int, pair<int, int>>> q;
	q.push({ 0, deer_pos });

	// 가장 가까운 산타 찾기
	vector<pair<int, int>> santa_pos_coord;
	while (!q.empty()) {
		int cnt = q.front().first;
		int row = q.front().second.first, col = q.front().second.second;
		q.pop();

		if (grid[row][col] > 0) {
			santa_pos_coord.push_back({row, col});
			int min_dist = get_distance(deer_pos, {row, col});
			while (!q.empty()) {
				if (grid[q.front().second.first][q.front().second.second] > 0) {
					int dist = get_distance(deer_pos, q.front().second);
					if (dist < min_dist) {
						santa_pos_coord.clear();
						min_dist = dist;
						santa_pos_coord.push_back(q.front().second);
					}
					else if (dist == min_dist) {
						santa_pos_coord.push_back(q.front().second);
					}
				}
				q.pop();
			}
			break;
		}

		for (int i = 0; i < 8; ++i) {
			int next_row = row + dr[i];
			int next_col = col + dc[i];
			if (is_valid_pos(next_row, next_col) 
				&& !visited[next_row][next_col]) {
				q.push({ cnt + 1, {next_row, next_col} });
				visited[next_row][next_col] = true;
			}
		}
	}

	sort(santa_pos_coord.begin(), santa_pos_coord.end(), compare_santa_pos);

	pair<int, int> target_pos = santa_pos_coord[0];

	pair<int, int> result;
	int min_dist = 5001;
	// 2. 목표 산타와 가장 가까워지는 방향으로, 목적지 설정하기
	for (int i = 0; i < 8; ++i) {
		int next_row = deer_pos.first + dr[i];
		int next_col = deer_pos.second + dc[i];
		if (is_valid_pos(next_row, next_col)) {
			int dist = get_distance(target_pos, { next_row, next_col });
			if (dist < min_dist) {
				result = { next_row, next_col };
				min_dist = dist;
				deer_dir = i;
			}
		}
	}

	return result;
}

pair<int, int> get_next_santa_pos(int num) {
	pair<int, int> pos = get_santa_pos(num);
	int row = pos.first, col = pos.second;

	// 루돌프와 가장 가까운 위치 찾기
	int min_dist = 501;
	pair<int, int> next_pos = { row, col };
	for (int i = 0; i < 8; i += 2) {
		int next_row = row + dr[i];
		int next_col = col + dc[i];

		if (is_valid_pos(next_row, next_col) && !is_exist_santa(next_row, next_col)) {
			//cout << "== 산타의 목적지 후보 ==\n";
			int dist = get_distance(deer_pos, {next_row, next_col});
			//cout << next_row << ", " << next_col << " 의 dist 값은 " << dist << '\n';
			if (dist < min_dist) {
				min_dist = dist;
				next_pos = { next_row, next_col };
				santa_dir = i;
			}
		}
	}

	//!!!! 가까워질 수 있는 방향으로 가지 못한다면 이동하지 않는다
	int cur_dist = get_distance(deer_pos, pos);
	int next_dist = get_distance(deer_pos, next_pos);

	if (cur_dist < next_dist) return pos;

	return next_pos;
}

// row, col 위치에서부터 dir 방향으로 산타와 상호작용
void interaction(int row, int col, int dir) {
	int end_row = row, end_col = col;
	while (is_valid_pos(end_row + dr[dir], end_col + dc[dir])) {
		end_row += dr[dir];
		end_col += dc[dir];
	}
	//cout << "swap 끝 지점: " << end_row << ", " << end_col << '\n';
	// 끝 지점에 산타가 존재하는 경우
	if (is_exist_santa(end_row, end_col)) {
		int santa_num = grid[end_row][end_col];
		failed[santa_num] = true;
	}

	dir = (dir + 4) % 8; // 반대 방향으로 swap
	while (!(end_row == row && end_col == col)) {
		int copy_row = end_row + dr[dir], copy_col = end_col + dc[dir];
		//cout << "swap: " << copy_row << ", " << copy_col << " 값을 " << end_row << ", " << end_col << " 위치로 복사합니다\n";
		grid[end_row][end_col] = grid[copy_row][copy_col];
		grid[copy_row][copy_col] = 0;
		end_row += dr[dir]; end_col += dc[dir];
	}
}

// 루돌프를 목적지로 이동
void move_deer(pair<int, int> dest) {
	// 목적지에 산타가 존재하지 않는 경우
	if (!is_exist_santa(dest.first, dest.second)) {
		grid[deer_pos.first][deer_pos.second] = 0;
		grid[dest.first][dest.second] = DEER;
		deer_pos = dest;
		return;
	}

	// 1. 산타의 점수 증가
	int santa_num = grid[dest.first][dest.second];
	score[santa_num] += c;

	// 2. 루돌프 자리 갱신
	grid[deer_pos.first][deer_pos.second] = 0;
	grid[dest.first][dest.second] = DEER;
	deer_pos = dest;

	// 3. 산타 밀기
	pair<int, int> santa_dest = { dest.first + dr[deer_dir] * c, dest.second + dc[deer_dir] * c};
	
	// 밖으로 밀려난 경우 -> 실패
	if (!is_valid_pos(santa_dest.first, santa_dest.second)) {
		go_out_santa(santa_num);
		return;
	}

	// 4. 밀쳐진 장소에 산타가 있는 경우 -> 상호작용
	if (is_exist_santa(santa_dest.first, santa_dest.second)) {
		interaction(santa_dest.first, santa_dest.second, deer_dir);
	}
	grid[santa_dest.first][santa_dest.second] = santa_num;

	// 5. 산타 기절
	comma[santa_num] = 2;
}

bool is_same_pos(pair<int, int> a, pair<int, int> b) {
	return a.first == b.first && a.second == b.second;
}

// start 위치에서 dest 위치로 산타를 옮기는 함수
void move_santa(pair<int, int> start, pair<int, int> dest) {
	// 시작점과 목적지가 똑같은 경우
	if (is_same_pos(start, dest)) return;

	// 목적지에 루돌프가 없는 경우
	if (!is_exist_deer(dest.first, dest.second)) {
		grid[dest.first][dest.second] = grid[start.first][start.second];
		grid[start.first][start.second] = 0;
		return;
	}

	// 1. 점수 획득
	int santa_num = grid[start.first][start.second];
	score[santa_num] += d;

	// 2. 산타 밀기
	int dir = (santa_dir + 4) % 8; // 이동방향의 반대 방향으로 충돌
	pair<int, int> santa_dest = { dest.first + dr[dir] * d, dest.second + dc[dir] * d };

	// 밖으로 밀려난 경우 -> 실패
	if (!is_valid_pos(santa_dest.first, santa_dest.second)) {
		go_out_santa(santa_num);
		return;
	}

	// 원래 위치 비우기
	grid[start.first][start.second] = 0;

	// 3. 밀쳐진 장소에 산타가 있는 경우 -> 상호작용
	if (is_exist_santa(santa_dest.first, santa_dest.second)) {
		//cout << santa_num << "이 " << santa_dest.first << ", " << santa_dest.second << " 로 이동하면서 충돌합니다\n";
		interaction(santa_dest.first, santa_dest.second, dir);
	}

	// 4. 산타 옮기기
	grid[santa_dest.first][santa_dest.second] = santa_num;

	// 5. 산타 기절
	comma[santa_num] = 2;
}

int main() {
	cin >> n >> m >> p >> c >> d;

	cin >> deer_pos.first >> deer_pos.second;
	grid[--deer_pos.first][--deer_pos.second] = DEER;

	for (int i = 0; i < p; ++i) {
		int santa, r, c;
		cin >> santa >> r >> c;
		grid[r - 1][c - 1] = santa;
	}

	//print_grid();

	while (m--) {
		if (is_over()) break;

		// 1. 루돌프 이동
		pair<int, int> pos = get_next_deer_pos();
		//cout << "루돌프의 다음 위치: " << pos.first << ", " << pos.second << '\n';
		move_deer(pos);

		// 2. 산타 이동
		for (int i = 1; i <= p; ++i) {
			if (!failed[i] && comma[i] == 0) {
				pair<int, int> dest = get_next_santa_pos(i);
				//cout << i << "번 산타의 목적지: " << dest.first << ", " << dest.second << '\n';
				move_santa(get_santa_pos(i), dest);
				//cout << "산타 이동 완료\n";
				//print_grid();
			}
		}

		update_comma();
		increase_score();

		//cout << "=== 격자 상태 ===\n";
		//print_grid();
	}

	for (int i = 1; i <= p; ++i) {
		cout << score[i] << ' ';
	}
	cout << '\n';

	return 0;
}