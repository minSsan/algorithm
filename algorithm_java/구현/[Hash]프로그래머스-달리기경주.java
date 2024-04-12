import java.util.*;

class Solution {
    // players: 현재 등수 순서대로 담긴 선수 이름 배열
    // callings: 해설진이 부른 이름을 담은 배열
    // -> 경주가 끝났을 때 1등부터 순서대로 배열에 담아서 리턴해라

    // 각 플레이어의 순위를 해시맵으로 관리한다.
    // calling을 순회하면서, 각 플레이어의 순위를 업데이트한다.
    // -> 순위 업데이트 과정
    // 1. 현재 호출된 플레이어의 등수를 해시맵에서 추출한다.
    // 2. 추출된 순위를 기준으로, answer의 값을 서로 스와핑한다.
    public String[] solution(String[] players, String[] callings) {
        String[] answer = players.clone();
        HashMap<String, Integer> map = new HashMap<>();
        // 0. 해시맵 초기화
        for (int i = 0; i < players.length; ++i) {
            map.put(players[i], i+1);
        }
        // 1. 순위 업데이트
        for (String called : callings) {
            int rank_index = map.get(called) - 1;
            if (rank_index == 0) continue;
            map.put(called, rank_index);
            map.put(answer[rank_index-1], rank_index+1);
            String tmp = answer[rank_index];
            answer[rank_index] = answer[rank_index-1];
            answer[rank_index-1] = tmp;
        }
        return answer;
    }
}