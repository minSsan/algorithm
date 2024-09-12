import java.io.*;
import java.util.*;

public class Main {
    private static boolean[] visited;
    private static ArrayList<Integer>[] graph;
    private static List<Integer> visitedList;

    private static void dfs(int x) {
        visited[x] = true;
        visitedList.add(x);
        for (int y : graph[x]) {
            if (!visited[y]) {
                dfs(y);
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int vertex = Integer.parseInt(st.nextToken());
        int line = Integer.parseInt(st.nextToken());
        int startVertex = Integer.parseInt(st.nextToken());

        graph = new ArrayList[vertex + 1];

        for (int i = 1; i <= vertex; ++i) {
            graph[i] = new ArrayList<>();
        }

        visited = new boolean[vertex + 1];
        for (int i = 0; i < line; ++i) {
            st = new StringTokenizer(br.readLine());
            int x = Integer.parseInt(st.nextToken());
            int y = Integer.parseInt(st.nextToken());

            graph[x].add(y);
            graph[y].add(x);
        }

        // 오름차순 방문
        for (int i = 1; i <= vertex; ++i) {
            Collections.sort(graph[i]);
        }

        dfs(startVertex);
        for (int visited : visitedList) {
            System.out.println(visited);
        }
    }
}