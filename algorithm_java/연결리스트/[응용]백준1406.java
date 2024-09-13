import java.io.*;
import java.util.*;

public class Main {
    private static String text;
    private static LinkedList<String> textList = new LinkedList<>();
    private static ListIterator<String> iter; // 커서의 위치
    private static String command;
    private static String value;

    private static void execute(String command) {
        switch (command) {
            case "L": // 커서를 왼쪽으로 한 칸 옮김
                if (iter.hasPrevious()) iter.previous();
                break;
            case "D": // 커서를 오른쪽으로 한 칸 옮김
                if (iter.hasNext()) iter.next();
                break;
            case "B": // 커서 왼쪽 문자를 삭제
                if (iter.hasPrevious()) {
                    iter.previous();
                    iter.remove();
                }
                break;
        }
    }

    private static void execute(String command, String value) {
        // 커서 왼쪽에 문자를 추가
        iter.add(value);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        // 1. text 입력 후 LinkedList 저장
        text = br.readLine();
        for (int i = 0; i < text.length(); ++i) {
            textList.add(text.substring(i, i+1));
        }
        iter = textList.listIterator();
        while (iter.hasNext()) {
            iter.next();
        }

        // 2. 명령어 차례대로 입력
        int m = Integer.parseInt(br.readLine());
        for (int i = 0; i < m; ++i) {
            st = new StringTokenizer(br.readLine());
            command = st.nextToken();

            if (command.equals("P")) {
                value = st.nextToken();
                execute("P", value);
            } else {
                execute(command);
            }
        }

        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        // 3. 명령어 모두 실행 후, linked list에 저장된 문자 출력
        for (String s : textList) {
            bw.write(s);
        }
        bw.write('\n');
        bw.flush();
        bw.close();
    }
}