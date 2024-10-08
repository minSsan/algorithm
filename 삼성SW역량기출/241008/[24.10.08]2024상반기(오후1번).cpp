// 소요 시간 - 2시간 30분
// 문제 링크 - https://www.codetree.ai/training-field/frequent-problems/company/samsung/problems

#include <iostream>
#include <queue>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define GAP 3 // forest에서 출발 선상에 해당하는 칸

using namespace std;

struct golem {
	int start_c; // 시작 열
	int d; // 출구 방향 정보
	int num; // 골렘 번호
};

int ans;
int r, c, k; // row, col, 정령 수
int forest[73][70]; // 숲에서의 골렘 상태
bool visited[73][70]; // 방문 상태 (bfs 탐색 사용)
bool is_exit[73][70]; // 해당 위치가 출구인지

int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };

void print_forest() {
	cout << "=== 골렘 상태 ===\n";
	for (int i = 0; i < r + GAP; ++i) {
		for (int j = 0; j < c; ++j) {
			cout << forest[i][j] << ' ';
		}
		cout << '\n';
	}
}

// 숲에 있는 골렘을 모두 내보내는 함수
void clear_forest() {
	for (int i = 0; i < r+GAP; ++i) {
		for (int j = 0; j < c; ++j) {
			forest[i][j] = 0;
		}
	}

	for (int i = 0; i < r + GAP; ++i) {
		for (int j = 0; j < c; ++j) {
			is_exit[i][j] = 0;
		}
	}
}

// visited 배열 초기화
void init_visited() {
	for (int i = 0; i < r+GAP; ++i) {
		for (int j = 0; j < c; ++j) {
			visited[i][j] = 0;
		}
	}
}

bool is_valid_pos(int pos_r, int pos_c) {
	return pos_r >= GAP && pos_r < r+GAP && pos_c >= 0 && pos_c < c;
}

bool is_valid_move_pos(int row, int col) {
	return row >= 0 && row < r + GAP && col >= 0 && col < c;
}

// 골렘 정보로 해당 골렘의 출구 위치를 반환
pair<int, int> get_exit_pos(golem info, int row, int col) {
	switch (info.d)
	{
	case UP:
		return { row - 1, col };
	case RIGHT:
		return { row, col + 1 };
	case DOWN:
		return { row + 1, col };
	case LEFT:
		return { row, col - 1 };
	default:
		return { row, col };
	}
}

// 골렘의 중앙 위치를 기반으로, 남쪽 이동 가능여부 반환
bool can_move_down(int row, int col) {
	return is_valid_move_pos(row + 1, col - 1) && forest[row + 1][col - 1] == 0
		&& is_valid_move_pos(row + 1, col + 1) && forest[row + 1][col + 1] == 0
		&& is_valid_move_pos(row + 2, col) && forest[row + 2][col] == 0;
}

bool can_move_left_down(int row, int col) {
	return is_valid_move_pos(row - 1, col - 1) && forest[row - 1][col - 1] == 0
		&& is_valid_move_pos(row, col - 2) && forest[row][col - 2] == 0
		&& is_valid_move_pos(row + 1, col - 1) && forest[row + 1][col - 1] == 0
		&& is_valid_move_pos(row + 1, col - 2) && forest[row + 1][col - 2] == 0
		&& is_valid_move_pos(row + 2, col - 1) && forest[row + 2][col - 1] == 0;
}

bool can_move_right_down(int row, int col) {
	return is_valid_move_pos(row - 1, col + 1) && forest[row - 1][col + 1] == 0
		&& is_valid_move_pos(row, col + 2) && forest[row][col + 2] == 0
		&& is_valid_move_pos(row + 1, col + 1) && forest[row + 1][col + 1] == 0
		&& is_valid_move_pos(row + 1, col + 2) && forest[row + 1][col + 2] == 0
		&& is_valid_move_pos(row + 2, col + 1) && forest[row + 2][col + 1] == 0;
}

// 주어진 골렘을 이동시키는 함수
pair<int, pair<int, int>> move_golem(golem info) { // 방향, {행, 열}
	int start_row = 1;
	int start_col = info.start_c;

	queue<pair<golem, pair<int, int>>> q;
	q.push({ info, {start_row, start_col} });

	while (!q.empty()) {
		auto cur = q.front();
		int row = cur.second.first, col = cur.second.second;
		golem cur_info = cur.first;
		q.pop();

		// 1. 남쪽 이동 확인
		if (can_move_down(row, col)) {
			q.push({ cur_info, {row+1, col} });
			//cout << "[남쪽] { " << row + 1 << ", " << col << " } 위치로 이동\n";
			continue;
		}
		//cout << "남쪽 이동 불가\n";

		// 2. 서쪽 이동 확인
		if (can_move_left_down(row, col)) {
			cur_info.d = (cur_info.d + 3) % 4;
			//cur_info.d = (cur_info.d + 3) % 4;
			q.push({ cur_info, {row + 1, col - 1} });
			//cout << "[서쪽] { " << row + 1 << ", " << col - 1 << " } 위치로 이동\n";
			//cout << "출구 방향: " << cur_info.d << '\n';
			continue;
		}
		//cout << "서쪽 이동 불가\n";

		// 3. 동쪽 이동 확인
		if (can_move_right_down(row, col)) {
			cur_info.d = (cur_info.d + 1) % 4;
			q.push({ cur_info, {row + 1, col + 1} });
			//cout << "[동쪽] { " << row + 1 << ", " << col + 1 << " } 위치로 이동\n";
			//cout << "출구 방향: " << cur_info.d << '\n';
			continue;
		}
		//cout << "동쪽 이동 불가\n";

		//cout << "[이동 완료] 최종 위치: { " << row << ", " << col << " }\n";
		return { cur_info.d, {row, col} };
	}

	//cout << "[이동 불가] 최종 위치: { " << start_row << ", " << start_col << " }\n";
	return { info.d, {start_row, start_col} };
}

// 골렘의 위치가 숲 내부인지 확인 + 골렘 위치 기록
bool is_valid_golem_pos(int row, int col, int num) {
	forest[row][col] = num;
	for (int i = 0; i < 4; ++i) {
		if (!is_valid_pos(row + dr[i], col + dc[i])) return false;
		forest[row + dr[i]][col + dc[i]] = num;
	}
	return true;
}

// 정령 움직인 후, 최대 row값 반환
int move_angel(int start_row, int start_col, golem info) { // 시작 위치, 골렘 정보	
	queue<pair<int, pair<int, int>>> q; // {골렘 번호, {행, 열}}
	init_visited();
	q.push({ info.num, {start_row, start_col} });
	visited[start_row][start_col] = true;

	// 현재 골렘의 출구 위치
	pair<int, int> exit_pos = get_exit_pos(info, start_row, start_col);
	is_exit[exit_pos.first][exit_pos.second] = true;
	//cout << "골렘 위치: " << start_row << ", " << start_col << '\n';
	//cout << "골렘 출구 위치: " << exit_pos.first << ", " << exit_pos.second << '\n';

	int max_row = 0;

	while (!q.empty()) {
		int cur_num = q.front().first;
		int row = q.front().second.first, col = q.front().second.second;
		q.pop();

		if (row > max_row) max_row = row;

		// 1. 현재 위치가 출구인 경우
		if (is_exit[row][col]) {
			for (int i = 0; i < 4; ++i) {
				int next_row = row + dr[i], next_col = col + dc[i];
				if (is_valid_pos(next_row, next_col) && !visited[next_row][next_col]
					&& forest[next_row][next_col] > 0) {
					q.push({ forest[next_row][next_col], {next_row, next_col}});
					visited[next_row][next_col] = true;
				}
			}
			continue;
		}

		// 2. 출구가 아닌 경우
		for (int i = 0; i < 4; ++i) {
			int next_row = row + dr[i], next_col = col + dc[i];
			if (is_valid_pos(next_row, next_col) && !visited[next_row][next_col]
				&& forest[next_row][next_col] == cur_num) {
				q.push({ cur_num, {next_row, next_col} });
				visited[next_row][next_col] = true;
			}
		}
	}

	return max_row;
}

int main() {
	cin >> r >> c >> k;
	for (int i = 1; i <= k; ++i) {
		int c, d;
		cin >> c >> d;
		c--;

		// 1. 골렘을 이동 순서에 맞게 이동시키기
		pair<int, pair<int, int>> result = move_golem({ c, d, i });
		int dir = result.first;
		pair<int, int> pos = result.second;

		// 2. 골렘의 몸 일부 벗어났는지 확인
		if (!is_valid_golem_pos(pos.first, pos.second, i)) {
			// 2-1. 벗어났을 경우, clear_forest 호출 후 continue
			clear_forest();
			continue;
		}

		// 3. 정령 움직이기 후 최대 row 값 반환
		int max_row = move_angel(pos.first, pos.second, { c, dir, i });

		// 4. ans 값 누적
		ans += max_row-2;
	}

	cout << ans << '\n';

	return 0;
}