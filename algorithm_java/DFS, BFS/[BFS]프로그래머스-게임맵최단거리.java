import java.util.*;

public class DFS {
    List<List<Integer>> graph = new ArrayList<>();
    boolean[] visited = new boolean[200];
    int cnt1 = 0;

    void dfs1(int start) {
        visited[start] = true;
        for (int i = 0; i < graph.get(start).size(); ++i) {
            if (start != i && graph.get(start).get(i) == 1 && !visited[i]) {
                dfs1(i);
            }
        }
    }

    // 그래프가 이차원 배열로 주어지는 경우
    void solution1(int n, int[][] computers) {
        // 0. int array -> List 세팅
        for (int i = 0; i < n; ++i) {
            graph.add(new ArrayList<>());
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                graph.get(i).add(computers[i][j]);
            }
        }
        // 1. dfs 탐색 시작
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && graph.get(i).get(j) == 1 && !visited[j]) {
                    ++cnt1;
                    dfs1(j);
                }
            }
        }
    }
}
