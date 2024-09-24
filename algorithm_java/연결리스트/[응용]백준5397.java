import java.io.*;
import java.util.*;

public class Main {
    private static int n;
    private static LinkedList<String> password = new LinkedList<>();
    private static ListIterator<String> cursor;

    private static String getDecodeResult(String inputs) {
        for (int i = 0; i < inputs.length(); ++i) {
            char c = inputs.charAt(i);
            switch (c) {
                case '-':
                    if (cursor.hasPrevious()) {
                        cursor.previous();
                        cursor.remove();
                    }
                    break;
                case '<':
                    if (cursor.hasPrevious()) {
                        cursor.previous();
                    }
                    break;
                case '>':
                    if (cursor.hasNext()) {
                        cursor.next();
                    }
                    break;
                default:
                    cursor.add(c + "");
                    break;
            }
        }

        StringBuilder sb = new StringBuilder();
        for (String s : password) {
            sb.append(s);
        }

        return sb.toString();
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        n = Integer.parseInt(br.readLine());

        for (int i = 0; i < n; ++i) {
            cursor = password.listIterator();
            bw.write(getDecodeResult(br.readLine()));
            bw.write('\n');
            password.clear();
        }
        bw.flush();
        bw.close();
    }
}