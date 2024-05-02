import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());

        int max_h = 0;

        StringTokenizer st2 = new StringTokenizer(br.readLine());
        int[] arr = new int[n];
        for (int i = 0; i < n; ++i) {
            arr[i] = Integer.parseInt(st2.nextToken());
            if (arr[i] > max_h) max_h = arr[i];
        }

        // 적어도 m 미터의 나무를 가져가기 위해 절단기에 설정할 수 있는 높이의 최댓값?

        // 높이를 1부터 설정 -> 각 나무의 높이에서 1을 뺀 값을 모두 합하면 가져간 나무 높이의 합이 된다.
        // 1부터 높이 최댓값(10억)까지 순회? -> 시간초과

        // 이분탐색: (0 미터 / max_h 미터) / 2 로 잘랐을 때
        // 나무 길이 합이 m보다 크면 max_h를 mid - 1 (크거나 같은 경우, 현재 저장된 결과 값보다 큰지 비교하고 결과 값을 갱신한다)
        // 나무 길이 합이 m보다 작으면 min_h를 mid + 1

        int answer = 0;
        int min = 0; int max = max_h; int mid;
        while (min <= max) {
            mid = (min + max) / 2;
            // 절단 나무 길이의 합 구하기
            long sum = 0;
            for (int i = 0; i < n; ++i) {
                if (arr[i] > mid) sum += arr[i] - mid;
            }

//            System.out.println("h: "+mid);
//            System.out.println("sum: "+sum);

            // 절단 길이의 합이 m보다 크거나 같은 경우 -> 절단 길이의 합을 줄여야 한다.
            if (sum >= m) {
                min = mid + 1;
                if (mid > answer) answer = mid;
                if (sum == m) break;
            } else {
                max = mid - 1;
            }
        }

        System.out.println(answer);
    }
}