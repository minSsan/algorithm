import java.util.*;

public class CollectionsPractice {
    public void solution() {
        List<Integer> list = new ArrayList<>();
        for (int i = 0; i < 10; ++i) {
            list.add(i);
        }
        // 복습 -> List ~ Array 형변환
        int[] arr = list.stream().mapToInt(i->i).toArray();

        System.out.println("최댓값: "+Collections.max(list));
        System.out.println("최솟값: "+Collections.min(list));

        // 오름차순 정렬
        System.out.println("오름차순 정렬");
        Collections.sort(list);
        for (int i : list) {
            System.out.println(i);
        }
        // 내림차순 정렬
        System.out.println("내림차순 정렬");
        Collections.sort(list, Collections.reverseOrder()); // 1
        list.sort(Collections.reverseOrder()); // 2
        for (int i : list) {
            System.out.println(i);
        }
        // 뒤집기
        System.out.println("뒤집기");
        Collections.reverse(list); // 뒤집기
        for (int i : list) {
            System.out.println(i);
        }

        System.out.println("이진 탐색으로 찾은 2의 위치: "+Collections.binarySearch(list, 2));
    }
}
