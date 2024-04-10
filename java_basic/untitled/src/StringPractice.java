import java.util.*;

public class Solution {
    public void solution() {
        String str = "1234";
        System.out.println("str: " + str);
        System.out.println("문자열 길이: " + str.length());
        System.out.println("문자열 자르기(0번 ~ 1번): " + str.substring(0, 2));
        System.out.println("문자 찾기(1번): " + str.charAt(1));
        System.out.println("인덱스 찾기('3'): " + str.indexOf('3'));
        str.indexOf(1);
    }
}
