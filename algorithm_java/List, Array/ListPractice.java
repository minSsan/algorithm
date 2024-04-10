import java.util.*;
public class ListPractice {
    public void solution() {
        List<String> list = new ArrayList<>();
        list.add("1");
        list.add("2");
        for (String s : list) {
            System.out.println(s);
        }

        System.out.println("0번째 원소: "+list.get(0));
        list.remove(1); // 1번 인덱스 원소 삭제
        list.clear(); // 모든 원소 삭제
        System.out.println("모든 원소 삭제 후 크기: "+list.size());
        list.add("1");
        list.add("2");
        list.removeIf(v -> Integer.parseInt(v) % 2 == 0);
        System.out.println("짝수 삭제");
        for (String s : list) {
            System.out.println(s);
        }

        int[] arr = {1, 2, 3, 4, 5};
        Arrays.stream(arr).forEach(v -> {
            System.out.println(v);
        });
        List<Integer> convertedList = new ArrayList<>();
        for (int i : arr) {
            convertedList.add(i);
        }

        List<Integer> intList = new ArrayList<>();
        intList.add(10);
        intList.add(9);
        intList.add(8);
        int[] arr2 = intList.stream().mapToInt(i->i).toArray();
        for (int n : arr2) {
            System.out.println(n);
        }
    }
}
