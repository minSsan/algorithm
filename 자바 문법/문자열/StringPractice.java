public class StringPractice {
    public void solution() {
        String str = "1234";
        System.out.println("str: " + str);
        System.out.println("문자열 길이: " + str.length());
        System.out.println("문자열 자르기(0번 ~ 1번): " + str.substring(0, 2));
        System.out.println("문자 찾기(1번): " + str.charAt(1));
        System.out.println("인덱스 찾기('3'): " + str.indexOf('3'));
        System.out.println("'4'를 '5'로 바꾸기: " + str.replace('4', '5'));
        System.out.println("'5'를 포함하는지: " + str.contains("5"));
        System.out.println("String을 split하여 각 원소를 출력");
        String[] strings = str.split("");
        for (String s : strings) {
            System.out.println(s);
        }
        System.out.println("=======");
        String str2 = "abcd";
        System.out.println("모두 대문자로 변경: "+str2.toUpperCase());
        System.out.println("ad와 사전순 비교: "+str2.compareTo("ad")); // 음수, 글자 차이 -> -2
        System.out.println("str을 Integer로 변경: "+Integer.parseInt(str));

        System.out.println("\n ==== 문자열을 수정해야 할 때 ====");
        StringBuilder sb = new StringBuilder(str);
        System.out.println("str에 56 추가: "+sb.append("56"));
        System.out.println("0번째 자리에 0 추가: "+sb.insert(0, "0"));
        System.out.println("5번 ~ 6번 문자열 삭제: "+sb.delete(5, 7));
        System.out.println("4번 문자열 삭제: "+sb.deleteCharAt(4));
        System.out.println("문자열 뒤집기: "+sb.reverse());
    }
}
