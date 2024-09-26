import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        int n = Integer.parseInt(br.readLine());
        int[] score = new int[n+1];
        for (int i = 1; i <= n; ++i) {
            score[i] = Integer.parseInt(br.readLine());
        }

        int[][] dp = new int[n+1][3];
        dp[1][1] = score[1];
        dp[1][2] = 0;
        if (n >= 2) {
            dp[2][1] = score[2];
            dp[2][2] = score[1] + score[2];
        }
        
        for (int i = 3; i <= n; ++i) {
            dp[i][1] = Math.max(dp[i-2][1], dp[i-2][2]) + score[i];
            dp[i][2] = dp[i-1][1] + score[i];
        }

        bw.write(String.valueOf(Math.max(dp[n][1], dp[n][2])));
        bw.write('\n');
        bw.flush();
        bw.close();
    }
}