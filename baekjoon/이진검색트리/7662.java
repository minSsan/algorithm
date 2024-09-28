import java.io.*;
import java.util.*;

public class Main {
    private final static TreeMap<Integer, Integer> dq = new TreeMap<>();
    private static void execute(char cmd, int n) {
        switch (cmd) {
            case 'D':
                if (dq.isEmpty()) break;

                // 1. 최솟값 삭제
                if (n == -1) {
                    Map.Entry<Integer, Integer> entry = dq.firstEntry();
                    if (entry.getValue() > 1) {
                        dq.put(entry.getKey(), entry.getValue()-1);
                    } else {
                        dq.remove(entry.getKey());
                    }
                }
                // 2. 최댓값 삭제
                else {
                    Map.Entry<Integer, Integer> entry = dq.lastEntry();
                    if (entry.getValue() > 1) {
                        dq.put(entry.getKey(), entry.getValue()-1);
                    } else {
                        dq.remove(entry.getKey());
                    }
                }
                break;
            case 'I':
                // 값 추가
                if (dq.containsKey(n)) {
                    dq.put(n, dq.get(n)+1);
                } else {
                    dq.put(n, 1);
                }
                break;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st;

        int t = Integer.parseInt(br.readLine());
        for (int i = 0; i < t; ++i) {
            dq.clear();
            int k = Integer.parseInt(br.readLine());
            for (int j = 0; j < k; ++j) {
                st = new StringTokenizer(br.readLine());
                char op = st.nextToken().charAt(0);
                int n = Integer.parseInt(st.nextToken());
                execute(op, n);
            }
            if (dq.isEmpty()) {
                bw.write("EMPTY\n");
            } else {
                bw.write(dq.lastEntry().getKey() + " " + dq.firstEntry().getKey() + '\n');
            }
        }
        bw.flush();
        bw.close();
    }
}
