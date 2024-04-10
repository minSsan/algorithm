import java.util.*;
public class PriorityQueuePractice {
    public void solution() {
        PriorityQueue<Integer> minPQ = new PriorityQueue<>(); // 최소힙
        PriorityQueue<Integer> maxPQ = new PriorityQueue<>(Collections.reverseOrder()); // 최대힙

        minPQ.add(1);
        minPQ.add(2);

        maxPQ.add(1);
        maxPQ.add(2);

        System.out.println("최소힙 top: "+minPQ.peek());
        System.out.println("최대힙 top: "+maxPQ.peek());

        System.out.println("최소힙 값 삭제");
        minPQ.remove();
        System.out.println("최소힙 크기: "+minPQ.size());

        System.out.println("최대힙 clear");
        maxPQ.clear();
        System.out.println("최대힙 isEmpty?: "+maxPQ.isEmpty());
    }
}
