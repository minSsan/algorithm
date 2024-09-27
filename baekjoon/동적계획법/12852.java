import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        int n = Integer.parseInt(br.readLine());
        int[] dp = new int[n+1];
        int[] tracking = new int[n+1];

        dp[1] = 0;
        tracking[1] = 0;

        if (n == 1) {
            bw.write("0\n");
            bw.write("1\n");
            bw.flush();
            bw.close();
            return;
        }

        dp[2] = 1;
        tracking[2] = 1;

        if (n == 2) {
            bw.write("1\n");
            bw.write("2 1\n");
            bw.flush();
            bw.close();
            return;
        }

        dp[3] = 1;
        tracking[3] = 1;

        for (int i = 4; i <= n; ++i) {
            dp[i] = dp[i-1];
            tracking[i] = i-1;

            if (i % 2 == 0) {
                if (dp[i/2] < dp[i]) {
                    dp[i] = dp[i/2];
                    tracking[i] = i/2;
                }
            }
            if (i % 3 == 0) {
                if (dp[i/3] < dp[i]) {
                    dp[i] = dp[i/3];
                    tracking[i] = i/3;
                }
            }
            dp[i] += 1;
        }

        bw.write(String.valueOf(dp[n]));
        bw.write('\n');

        bw.write(n + " ");
        int index = n;
        while (tracking[index] != 0) {
            bw.write(tracking[index] + " ");
            index = tracking[index];
        }
        bw.write('\n');
        bw.flush();
        bw.close();
    }
}