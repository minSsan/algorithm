import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        int n = Integer.parseInt(br.readLine());
        List<String> arr = new ArrayList<>();
        for (int i = 0; i < n; ++i) {
            arr.add(br.readLine());
        }

        arr.sort(new CustomComparator());

        for (int i = 0; i < n; ++i) {
            bw.write(arr.get(i));
            bw.write('\n');
        }
        bw.flush();
        bw.close();
    }
}

class CustomComparator implements Comparator<String> {
    @Override
    public int compare(String a, String b) {
        if (a.length() < b.length()) return -1;
        else if (a.length() > b.length()) return 1;
        int a_sum = 0, b_sum = 0;
        for (int i = 0; i < a.length(); ++i) {
            if (a.charAt(i) >= '0' && a.charAt(i) <= '9') {
                a_sum += a.charAt(i) - '0';
            }
            if (b.charAt(i) >= '0' && b.charAt(i) <= '9') {
                b_sum += b.charAt(i) - '0';
            }
        }

        if (a_sum < b_sum) return -1;
        else if (a_sum > b_sum) return 1;

        if (a.compareTo(b) < 0) return -1;
        else if (a.compareTo(b) > 0) return 1;

        return 0;
    }
}