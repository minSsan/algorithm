import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // n 입력
        int n = Integer.parseInt(br.readLine());
        // 리스트 입력
        StringTokenizer st = new StringTokenizer(br.readLine());
        int[] nums = new int[n];
        for (int i = 0; i < n; ++i) {
            nums[i] = Integer.parseInt(st.nextToken());
        }
        // x 입력
        int x = Integer.parseInt(br.readLine());

        int result = 0;
        boolean[] isExist = new boolean[2000001]; // n이 배열 내에 존재하는지 확인하는 배열
        for (int i = 0; i < n; ++i) {
            int target = x - nums[i];
            if (target >= 0 && target <= x && isExist[target]) {
                ++result;
            }
            isExist[nums[i]] = true;
        }

        System.out.println(result);
    }
}