class Solution {
    boolean[] visited = new boolean[200];

    void dfs(int start, int n, int[][] computers) {
        visited[start] = true;
        for (int i = 0; i < n; ++i) {
            if (computers[start][i] == 1 && !visited[i]) {
                dfs(i, n, computers);
            }
        }
    }

    public int solution(int n, int[][] computers) {
        int answer = 0;
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                ++answer;
                dfs(i, n, computers);
            }
        }
        return answer;
    }
}