import java.util.*;

public class StackPractice {
    public void solution() {
        Stack<Integer> stack = new Stack<>();
        stack.push(1);
        stack.pop();
        stack.clear();
        stack.size();
        if (stack.empty()) {
            System.out.println("스택이 비어있음");
        }
        System.out.println("스택에 1이 있는가?: "+stack.contains(1));
        stack.push(1);
        if (!stack.empty()) {
            System.out.println("top: "+stack.peek());
        }
        System.out.println("스택 크기: "+stack.size());
    }
}
