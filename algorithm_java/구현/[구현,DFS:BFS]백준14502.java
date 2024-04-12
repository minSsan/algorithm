import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

// 0: 빈칸, 1: 벽, 2: 바이러스
public class Main {
    static int[] dr = {-1, 1, 0, 0};
    static int[] dc = {0, 0, -1, 1};

    static int bfs(int[][] _map, int n, int m) {
        int[][] map = new int[n][m];
        for (int i = 0; i < n; ++i) {
            map[i] = _map[i].clone();
        }

        boolean[][] visited = new boolean[n][m];
        Queue<List<Integer>> q = new LinkedList<>();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (map[i][j] == 2) {
                    List<Integer> tmp = new ArrayList<>();
                    tmp.add(i);
                    tmp.add(j);
                    q.add(tmp);
                    visited[i][j] = true;
                }
            }
        }

        while (!q.isEmpty()) {
            List<Integer> pos = q.peek();
            int current_row = pos.get(0);
            int current_col = pos.get(1);
            q.remove();
            for (int i = 0; i < 4; ++i) {
                int next_row = current_row + dr[i];
                int next_col = current_col + dc[i];
                if (next_row < 0 || next_row >= n || next_col < 0 || next_col >= m) continue;
                if (visited[next_row][next_col]) continue;
                if (map[next_row][next_col] != 0) continue;
                List<Integer> tmp = new ArrayList<>();
                tmp.add(next_row);
                tmp.add(next_col);
                q.add(tmp);
                visited[next_row][next_col] = true;
                map[next_row][next_col] = 2;
            }
        }

        int answer = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (map[i][j] == 0) ++answer;
            }
        }
        return answer;
    }

    public static void main(String[] args) throws IOException {
        int answer = 0;

        // 0. 입력
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());
        int[][] map = new int[n][m];

        List<int[]> coord = new ArrayList<>(); // 벽을 세울 후보지
        for (int i = 0; i < n; ++i) {
            st = new StringTokenizer(br.readLine());
            for (int j = 0; j < m; ++j) {
                map[i][j] = Integer.parseInt(st.nextToken());
                // 빈칸을 벽을 세울 수 있는 후보지로 정한다
                if (map[i][j] == 0) {
                    int[] tmp = {i, j};
                    coord.add(tmp);
                }
            }
        }
        // 1. 벽을 세울 위치 세 곳을 정한다(모든 경우의 수를 찾는다)
        for (int i = 0; i < coord.size()-2; ++i) {
            for (int j = i+1; j < coord.size()-1; ++j) {
                for (int k = j+1; k < coord.size(); ++k) {
                    int[] first = coord.get(i);
                    int[] second = coord.get(j);
                    int[] third = coord.get(k);
                    map[first[0]][first[1]] = 1;
                    map[second[0]][second[1]] = 1;
                    map[third[0]][third[1]] = 1;
                    int tmp = bfs(map, n, m);
                    answer = Math.max(answer, tmp);
                    map[first[0]][first[1]] = 0;
                    map[second[0]][second[1]] = 0;
                    map[third[0]][third[1]] = 0;
                }
            }
        }
        // 2. 각 경우에 대해서 안전 영역의 크기를 구한다
        // 3. 2번에서 찾은 값 중에서 가장 작은 값이 정답
        System.out.println(answer);
    }
}
