#include <iostream>
#include <queue>

using namespace std;

#define EMPTY 0
#define TRAP 1
#define WALL 2

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

int l, n, q; // l: 체스 크기, n: 기사 수, q: 명령

struct knight {
	int damage; // 받은 데미지
	int k; // 초기 체력
	int w; // 가로
	int h; // 세로
};

pair<int, int> knight_pos[31];

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

int knight_num[41][41];
int grid[41][41];
knight knight_info[31];
bool damage[31]; // n번 기사가 이번 턴에 데미지를 입었는지 확인

bool visited[41][41];

void init_visited() {
	for (int i = 0; i < l; ++i) {
		for (int j = 0; j < l; ++j) {
			visited[i][j] = false;
		}
	}
}

void print_knight() {
	for (int i = 0; i < l; ++i) {
		for (int j = 0; j < l; ++j) {
			cout << knight_num[i][j] << ' ';
		}
		cout << '\n';
	}
}

// knight_num 배열을 토대로 knight_pos 배열 값을 설정
void update_knight_pos() {
	// 1. 초기화
	for (int i = 1; i <= n; ++i) {
		knight_pos[i] = {-1, -1};
	}
	// 2. input - 가장 작은 r,c 값을 기록
	for (int i = l-1; i >= 0; --i) {
		for (int j = l-1; j >= 0; --j) {
			int num = knight_num[i][j];
			knight_pos[num] = { i, j };
		}
	}
}

bool is_valid_pos(int r, int c) {
	return r >= 0 && r < l && c >= 0 && c < l;
}

void init_damage() {
	for (int i = 1; i <= n; ++i) {
		damage[i] = false;
	}
}

// 이동방향으로 움직여야하는 위치 정보들
vector<pair<int, pair<int, int> > > move_pos; // {기사 번호, {행, 열}}

bool can_move(int num, int dir) {
	init_visited();
	move_pos.clear();

	int row = knight_pos[num].first;
	int col = knight_pos[num].second;

	queue < pair<int, int> > q;
	q.push({ row, col });
	move_pos.push_back({ num, {row, col} });
	visited[row][col] = true;

	while (!q.empty()) {
		int r = q.front().first;
		int c = q.front().second;
		q.pop();

		if (knight_num[r][c] > 0) {
			int target = knight_num[r][c];
			queue<pair<int, int>> tmp;
			tmp.push({ r, c });

			while (!tmp.empty()) {
				int cur_r = tmp.front().first;
				int cur_c = tmp.front().second;
				tmp.pop();

				for (int i = 0; i < 4; ++i) {
					int tmp_next_r = cur_r + dr[i];
					int tmp_next_c = cur_c + dc[i];
					// 같은 기사 영역만 넣는다
					if (is_valid_pos(tmp_next_r, tmp_next_c)
						&& !visited[tmp_next_r][tmp_next_c]
						&& knight_num[tmp_next_r][tmp_next_c] == target) {
						tmp.push({ tmp_next_r, tmp_next_c });
						q.push({ tmp_next_r, tmp_next_c });
						move_pos.push_back({ target, {tmp_next_r, tmp_next_c}});
						visited[tmp_next_r][tmp_next_c] = true;
					}
				}
			}
		}

		int next_r = r + dr[dir];
		int next_c = c + dc[dir];

		// 이동하지 못하는 공간인 경우
		if ((!is_valid_pos(next_r, next_c) || grid[next_r][next_c] == WALL)) {
			return false;
		}

		if (knight_num[next_r][next_c] > 0 && !visited[next_r][next_c]) {
			q.push({next_r, next_c});
			move_pos.push_back({ knight_num[next_r][next_c], {next_r, next_c} });
			visited[next_r][next_c] = true;
		}
	}
	return true;
}

// 시작 위치가 pos인 기사를 전장 배열에서 제거한다.
void remove_knight(int num, pair<int, int> pos) {
	int start_r = pos.first;
	int start_c = pos.second;

	knight gisa = knight_info[num];
	int end_r = start_r + gisa.h;
	int end_c = start_c + gisa.w;

	for (int i = start_r; i < end_r; ++i) {
		for (int j = start_c; j < end_c; ++j) {
			knight_num[i][j] = 0;
		}
	}
}

// 데미지 대상자 기록
void write_damage(int num) {
	init_damage();
	for (int i = 0; i < move_pos.size(); ++i) {
		int t = move_pos[i].first;
		if (t != num) damage[t] = true;
	}
}

// move_pos에 있는 애들을 dir 방향으로 모두 이동시킨다.
void push_knight(int dir) {
	// 이동하는 기사를 모두 삭제
	for (int i = 0; i < move_pos.size(); ++i) {
		int num = move_pos[i].first;
		pair<int, int> pos = knight_pos[num];
		remove_knight(num, pos);
	}

	for (int i = 0; i < move_pos.size(); ++i) {
		int num = move_pos[i].first;
		pair<int, int> pos = move_pos[i].second;
		int next_r = pos.first + dr[dir];
		int next_c = pos.second + dc[dir];

		knight_num[next_r][next_c] = num;
	}

	update_knight_pos();
}

// 현재 전장을 기준으로 데미지를 계산한다
void calc_damage(int num) {
	for (int i = 0; i < l; ++i) {
		for (int j = 0; j < l; ++j) {	
			int kn_num = knight_num[i][j];
			if (kn_num == num || !damage[kn_num]) continue;
			if (grid[i][j] == TRAP && kn_num > 0) {
				knight_info[kn_num].damage++;
				//cout << kn_num << " 번 기사가 데미지를 입음\n";
			}
		}
	}
}

// 기사가 전장에서 사라진 기사인지 확인
bool is_failed(knight kn) {
	return kn.damage >= kn.k;
}

// damage >= k 인 기사를 전장에서 내보낸다.
void exit_knight() {
	for (int i = 1; i <= n; ++i) {
		knight kn = knight_info[i];
		if (kn.damage >= kn.k) {
			pair<int, int> pos = knight_pos[i];
			remove_knight(i, pos);
		}
	}
}

void print_result() {
	int result = 0;

	for (int i = 1; i <= n; ++i) {
		knight kn = knight_info[i];
		if (!is_failed(kn)) {
			result += kn.damage;
		}
	}

	cout << result << '\n';
}

int main() {
	cin >> l >> n >> q;
	for (int i = 0; i < l; ++i) {
		for (int j = 0; j < l; ++j) {
			cin >> grid[i][j];
		}
	}
	for (int i = 1; i <= n; ++i) {
		int r, c, h, w, k;
		cin >> r >> c >> h >> w >> k;
		knight_info[i] = {0, k, w, h};
		for (int row = r-1; row < r-1 + h; ++row) {
			for (int col = c-1; col < c-1 + w; ++col) {
				knight_num[row][col] = i;
			}
		}
	}
	update_knight_pos();

	//print_knight();
	for (int i = 0; i < q; ++i) {
		int num, d; // 기사 번호, 방향
		cin >> num >> d;

		// 기사가 쓰러진 경우, 이동 불가능할 경우
		if (is_failed(knight_info[num])) {
			continue;
		}

		if (!can_move(num, d)) {
			continue;
		}
		// num을 제외한 밀쳐진 기사들의 데미지 여부 기록
		write_damage(num);

		// 1. 이동 가능할 경우, knight_num 업데이트
		push_knight(d);

		//cout << "이동 후\n";
		//print_knight();

		// 2. 데미지 검사
		calc_damage(num);
		
		// 3. 데미지가 기준 이상인 경우 전장에서 내보낸다.
		exit_knight();
	}

	print_result();

	return 0;
}