import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        // 입력
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        int[] arr = new int[n];
        StringTokenizer st = new StringTokenizer(br.readLine());
        for (int i = 0; i < n; ++i) {
            int value = Integer.parseInt(st.nextToken());
            arr[i] = value;
        }
        // 문제풀이
        int answer = 0;
        // 1. 오름차순 정렬
        Arrays.sort(arr);
        // 2. 값을 하나씩 탐색
        for (int i = 0; i < n; ++i) {
            int current_value = arr[i];
            // 2-1. 현재 보고 있는 값이 좋은 수인지 검사한다. (투 포인터)
            int start = 0; int end = n-1;

            if (start == i) ++start;
            if (end == i) --end;
            while (start < end) {
                int sum = arr[start] + arr[end];
                if (start != i && end != i && sum == current_value) {
//                    System.out.println(current_value+"는 좋은 수");
                    ++answer;
                    break;
                }
                if (sum > current_value) {
                    if (--end == i) --end;
                } else {
                    if (++start == i) ++start;
                }
            }
        }
        System.out.println(answer);
    }
}