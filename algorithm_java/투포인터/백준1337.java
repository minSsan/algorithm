import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        int[] arr = new int[n];
        for (int i = 0; i < n; ++i) {
            arr[i] = Integer.parseInt(br.readLine());
        }

        Arrays.sort(arr);

        int start = 0; int end = 0;
        int answer = 4; int len;
        while (end < n && start <= end) {
            len = arr[end] - arr[start] + 1;

            if (len > 5) {
                start++;
            } else {
                answer = Math.min(answer, 4 - (end - start));
                end++;
            }
        }

        System.out.println(answer);
    }
}