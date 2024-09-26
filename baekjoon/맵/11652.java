import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        Map<Long, Integer> note = new HashMap<>();
        Long max_v = -(2L << 62) - 1L;
        int max_cnt = 0;

        int n = Integer.parseInt(br.readLine());

        for (int i = 0; i < n; ++i) {
            Long v = Long.parseLong(br.readLine());
            note.put(v, note.getOrDefault(v, 0) + 1);
            if (note.get(v) > max_cnt) {
                max_cnt = note.get(v);
                max_v = v;
            } else if (note.get(v) == max_cnt) {
                max_v = Math.min(max_v, v);
            }
        }

        bw.write(max_v.toString());
        bw.write('\n');
        bw.flush();
        bw.close();
    }
}