import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());
        Map<String, Integer> nameToNum = new HashMap<>();
        String[] numToName = new String[n+1];
        for (int i = 1; i <= n; ++i) {
            String poketmon = br.readLine();
            nameToNum.put(poketmon, i);
            numToName[i] = poketmon;
        }

        for (int i = 0; i < m; ++i) {
            String s = br.readLine();
            if (Character.isAlphabetic(s.charAt(0))) {
                bw.write(String.valueOf(nameToNum.get(s)));
            } else {
                bw.write(String.valueOf(numToName[Integer.parseInt(s)]));
            }
            bw.write('\n');
        }
        bw.flush();
        bw.close();
    }
}
