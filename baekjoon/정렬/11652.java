import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        List<Long> arr = new ArrayList<>();
        int n = Integer.parseInt(br.readLine());

        for (int i = 0; i < n; ++i) {
            arr.add(Long.parseLong(br.readLine()));
        }

        arr.sort(Comparator.naturalOrder()); // 오름차순 정렬
        Long max_num = arr.get(0);
        int max_cnt = 1;
        int cur_cnt = 1;
        for (int i = 1; i < n; ++i) {
            if (arr.get(i).compareTo(arr.get(i-1)) == 0) {
                cur_cnt++;
            }
            else {
                if (cur_cnt > max_cnt) {
                    max_cnt = cur_cnt;
                    max_num = arr.get(i-1);
                }
                cur_cnt = 1;
            }
        }
        if (cur_cnt > max_cnt) {
            max_num = arr.get(n-1);
        }

        bw.write(max_num.toString());
        bw.write('\n');
        bw.flush();
        bw.close();
    }
}