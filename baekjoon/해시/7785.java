import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st;

        Map<String, Boolean> logs = new HashMap<>();

        int n = Integer.parseInt(br.readLine());
        for (int i = 0; i < n; ++i) {
            st = new StringTokenizer(br.readLine());
            String name = st.nextToken();
            String status = st.nextToken();

            if (status.equals("enter")) {
                logs.put(name, true);
            } else {
                logs.put(name, false);
            }
        }

        List<String> exist = new ArrayList<>();
        for (String s : logs.keySet()) {
            if (logs.get(s)) {
                exist.add(s);
            }
        }

        exist.sort(new CustomComparator());

        for (String s : exist) {
            bw.write(s);
            bw.write('\n');
        }
        bw.flush();
        bw.close();
    }
}

class CustomComparator implements Comparator<String> {
    @Override
    public int compare(String a, String b) {
        int compareValue = a.compareTo(b);
        if (compareValue > 0) return -1;
        if (compareValue == 0) return 0;
        return 1;
    }
}