#include <iostream>
#include <vector>

using namespace std;

// ? 그래프가 있다고 쳤을때 
// ? 입력: 부모 노드 리스트 / 찍을 스킬 리스트 가 들어올 것임 (단, 리스트의 최대 길이는 10,000)
// ? 최종적으로 찍어야 하는 스킬 개수를 출력하시오

int node_size;
int skill_size;

int solution(int* node_list, int* skill_list) { 
    int skill, current_node, result = 1; // 부모 노드 포함한 상태에서 시작
    vector<int> visited(node_size, 0);
    visited[0] = 1; // 부모 노드 포함한 상태에서 시작

    for (int i = 0; i < skill_size; ++i) {
        skill = skill_list[i]; 

        visited[skill] = 1; result++; 
        current_node = node_list[skill];

        while (current_node != 0) { 
            if (visited[current_node] == 0) {
                result++; 
                visited[current_node] = 1;
            } else { // 이미 방문한 노드부터는 count하지 않아도 된다.
                break;
            }
            current_node = node_list[current_node]; 
        }
    }

    return result;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int case1_node[] = {0, 4, 0, 4, 0, 2};
    int case1_skill[] = {1, 2};
    node_size = sizeof(case1_node) / sizeof(*case1_node);
    skill_size = sizeof(case1_skill) / sizeof(*case1_skill);
    cout << solution(case1_node, case1_skill) << '\n';

    int case2_node[] = {0, 0, 1, 2};
    int case2_skill[] = {2};
    node_size = sizeof(case2_node) / sizeof(*case2_node);
    skill_size = sizeof(case2_skill) / sizeof(*case2_skill);
    cout << solution(case2_node, case2_skill) << '\n';

    int case3_node[] = {0, 0, 0, 0, 1, 1, 2};
    int case3_skill[] = {5, 6};
    node_size = sizeof(case3_node) / sizeof(*case3_node);
    skill_size = sizeof(case3_skill) / sizeof(*case3_skill);
    cout << solution(case3_node, case3_skill) << '\n';


    return 0;
}