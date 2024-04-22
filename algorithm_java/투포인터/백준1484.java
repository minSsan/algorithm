import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        // 값 입력
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int G = Integer.parseInt(br.readLine());

        List<Integer> answer = new ArrayList<>();

        int past = 1; int current = 2;
        while (past < current) {
            int value = current*current - past*past;
            if (value == G) {
                answer.add(current);
                ++current;
                continue;
            }

            if (value < G) {
                ++current;
            } else {
                ++past;
            }
        }

        if (answer.isEmpty()) {
            System.out.println(-1);
            return ;
        }

        int[] ans = answer.stream().mapToInt(i -> i).toArray();
        Arrays.sort(ans);
        for (int n : ans) {
            System.out.println(n);
        }
    }
}