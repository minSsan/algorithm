import java.util.*;

public class QueuePractice {
    public void solution() {
        Queue<Integer> q = new LinkedList<>();
        q.add(1);
        q.add(2);
        System.out.println("가장 앞에 있는 값: "+q.peek());

        System.out.println("front 값 삭제");
        q.remove();

        System.out.println("가장 앞에 있는 값: "+q.peek());
        q.clear();
        System.out.println("크기: "+q.size());
    }
}
