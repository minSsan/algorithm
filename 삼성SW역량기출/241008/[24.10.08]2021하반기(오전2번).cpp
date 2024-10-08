// 소요 시간 - 3시간 16분
// 문제 링크 - https://www.acmicpc.net/problem/23289

#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

#define EMPTY 0 // 빈 칸
// 온풍기 정보
#define RIGHT_DEVICE 1 // 오른쪽
#define LEFT_DEVICE 2 // 왼쪽
#define UP_DEVICE 3 // 위
#define DOWN_DEVICE 4 // 아래
#define INVEST 5 // 온도 조사 칸

#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3

using namespace std;

struct node {
	int row;
	int col;
	int temp; // 온기
};

int ans;

int r, c, k;
int w;
int grid[20][20]; // 온풍기 정보
int temp[20][20]; // i, j의 온도 정보
bool wall[20][20][4];
vector<pair<int, int>> invest_pos;

int diff[20][20]; // 온풍기에 의해 변화한 온도 값

// 1. 우측, 좌측, 위, 아래 순서
int dr[4][3][2] = {
	// 2. 좌측 대각선, 직선, 우측 대각선
	{
		{-1, 0}, {0, 0}, {1, 0}
	},
	{
		{-1, 0}, {0, 0}, {1, 0}
	},
	{
		{0, -1}, {-1, 0}, {0, -1}
	},
	{
		{0, 1}, {1, 0}, {0, 1}
	}
};

// 1. 우측, 좌측, 위, 아래 순서
int dc[4][3][2] = {
	// 2. 좌측 대각선, 직선, 우측 대각선
	{
		{0, 1}, {1, 0}, {0, 1}
	},
	{
		{0, -1}, {-1, 0}, {0, -1}
	},
	{
		{-1, 0}, {0, 0}, {1, 0}
	},
	{
		{1, 0}, {0, 0}, {-1, 0}
	}
};

void print_temp() {
	cout << "=====온도 상태=====\n";
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			cout << temp[i][j] << "   ";
		}
		cout << '\n';
	}
}

void print_diff() {
	cout << "====diff====\n";
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			cout << diff[i][j] << "   ";
		}
		cout << '\n';
	}
}

bool is_valid_pos(int row, int col) {
	return row >= 0 && row < r && col >= 0 && col < c;
}

// 현재 위치와 다음 위치 사이에 벽이 존재하는지 확인
bool is_exist_wall(int cur_r, int cur_c, int next_r, int next_c) {
	// 1. 가로 방향
	// 1-1. 다음 위치가 우측
	if (next_c == cur_c + 1) {
		return wall[next_r][next_c][LEFT];
	}
	// 1-2. 다음 위치가 좌측
	if (next_c == cur_c - 1) {
		return wall[next_r][next_c][RIGHT];
	}
	// 2. 세로 방향
	// 2-1. 다음 위치가 위
	if (next_r == cur_r - 1) {
		return wall[next_r][next_c][DOWN];
	}
	// 2-2. 다음 위치가 아래
	if (next_r == cur_r + 1) {
		return wall[next_r][next_c][UP];
	}
	// 같은 위치인 경우
	return false;
}

// 하나의 온풍기를 가동하여 diff 배열 업데이트
void on_one_device(int info, int start_r, int start_c) { // 어느 방향의 온풍기인지, 어느 위치에 있는지
	bool visited[20][20];
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) visited[i][j] = 0;
	}

	//cout << "{ " << r << ", " << c << " } 위치 온풍기의 처음 열기 도착지점은 ";
	// 1. 온풍기 방향에 따라, 초기 위치 결정
	switch (info)
	{
	case RIGHT_DEVICE:
		start_c += 1;
		break;
	case LEFT_DEVICE:
		start_c -= 1;
		break;
	case UP_DEVICE:
		start_r -= 1;
		break;
	case DOWN_DEVICE:
		start_r += 1;
		break;
	default:
		break;
	}

	//cout << "{ " << r << ", " << c << " }\n";
	
	queue<node> q;
	q.push({start_r, start_c, 5});
	visited[start_r][start_c] = true;

	while (!q.empty()) {
		int row = q.front().row, col = q.front().col, tmp = q.front().temp;
		q.pop();

		diff[row][col] += tmp;

		// 열기가 1일 경우, 더이상 확산시킬 열기가 존재하지 않음
		if (tmp == 1) continue;

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
	}
}

void init_diff() {
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			diff[i][j] = 0;
		}
	}
}

// 모든 온풍기를 가동하여 온도 값 변화시키기
void on_all_device() {
	init_diff();

	// 1. 온풍기 가동
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			// 온풍기가 존재하는 경우
			if (grid[i][j]) {
				// diff 배열 업데이트
				on_one_device(grid[i][j], i, j);
			}
		}
	}

	// 2. 온도 합 더하기
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			temp[i][j] += diff[i][j];
		}
	}
}

// 동, 남 방향만 조사
int dr_adjust[2] = {0, 1};
int dc_adjust[2] = {1, 0};

// 온도 조절
void adjust_temp() {
	init_diff();

	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			for (int k = 0; k < 2; ++k) {
				int next_row = i + dr_adjust[k];
				int next_col = j + dc_adjust[k];
				if (is_valid_pos(next_row, next_col) && !is_exist_wall(i, j, next_row, next_col)) {
					int interval = abs(temp[next_row][next_col] - temp[i][j]) / 4;
					if (temp[next_row][next_col] > temp[i][j]) {
						diff[next_row][next_col] -= interval;
						diff[i][j] += interval;
					}
					else if (temp[next_row][next_col] < temp[i][j]) {
						diff[next_row][next_col] += interval;
						diff[i][j] -= interval;
					}
				}
			}
		}
	}

	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			temp[i][j] = temp[i][j] + diff[i][j];
		}
	}
}

// 가장 바깥쪽 위치의 온도를 1씩 감소
void decrease_temp() {
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			if (i == 0 || i == r-1) {
				temp[i][j] = max(0, temp[i][j]-1);
			}
			else if (j == 0 || j == c - 1) {
				temp[i][j] = max(0, temp[i][j]-1);
			}
		}
	}
}

bool is_over() {
	if (ans > 100) return true;
	for (pair<int, int> p : invest_pos) {
		if (temp[p.first][p.second] < k) return false;
	}
	return true;
}

int main() {
	cin >> r >> c >> k;
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			int input_n;
			cin >> input_n;
			if (input_n == INVEST) {
				invest_pos.push_back({ i, j });
			}
			else grid[i][j] = input_n;
		}
	}
	cin >> w;
	for (int i = 0; i < w; ++i) {
		int x, y, t;
		cin >> x >> y >> t;

		if (t == 0) {
			// (x, y) ~ (x-1, y) 사이 벽
			wall[x - 1][y - 1][UP] = true;
			wall[x - 2][y - 1][DOWN] = true;
		}
		else {
			// (x, y) ~ (x, y+1) 사이 벽
			wall[x - 1][y - 1][RIGHT] = true;
			wall[x - 1][y][LEFT] = true;
		}
	}

	while (!is_over()) {
		// 1. 각 온풍기에서 바람이 나오고, 각 온풍기에 의해 변한 온도 반영
		on_all_device();

		// 2. 온도를 조절한다.
		adjust_temp();

		// 3. 온도가 1 이상인 가장 바같쪽 칸의 온도를 1씩 감소시킨다.
		decrease_temp();

		// 4. 초콜릿을 하나 먹는다.
		ans++;
	}

	if (ans > 100) {
		cout << 101 << '\n';
	}
	else {
		cout << ans << '\n';
	}
	
	return 0;
}