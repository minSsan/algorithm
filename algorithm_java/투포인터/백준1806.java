import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int s = Integer.parseInt(st.nextToken());

        st = new StringTokenizer(br.readLine());
        int[] arr = new int[n];
        for (int i = 0; i < n; ++i) {
            arr[i] = Integer.parseInt(st.nextToken());
        }

        int answer = n+1;
        int start = 0; int end = 0;
        int sum = arr[0];
        while (true) {
            if (sum >= s) {
                answer = Math.min(answer, end - start + 1);
            }

            // sum 값이 s보다 작거나 같으면 늘린다
            if (sum <= s) {
                if (end+1 >= n) break;
                sum += arr[++end];
            } else {
                if (start+1 >= n) break;
                sum -= arr[start++];
            }
        }

        if (answer == n+1) {
            System.out.println(0);
        } else {
            System.out.println(answer);
        }
    }
}