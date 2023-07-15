#include <string>
#include <vector>

using namespace std;

// 7(7)
// 3(10) 8(15)
// 8(18) 1(16) 0(15)
// 2(20) 7(25) 4(20) 4(19)
// 4(24) 5(30) 2(27) 6(26) 5(24)

// [row+1][col], [row+1][col+1] 만 이동 가능
// [row-1][col] | [row-1][col-1]

int solution(vector<vector<int>> triangle) {
    int answer = triangle[0][0];
    
    int dx[2] = {0, -1};
    int dy[2] = {-1, -1};
    
    for (int row = 1; row < triangle.size(); ++row) {
        for (int col = 0; col < row+1; ++col) {
            int max = 0;
            for (int i = 0; i < 2; ++i) {
                int search_row = row + dy[i];
                int search_col = col + dx[i];
                
                if ((search_row >= 0 && search_col >= 0) && (search_col <= search_row) && triangle[search_row][search_col] > max) {
                    max = triangle[search_row][search_col];
                }
            }
            triangle[row][col] += max;
            if (triangle[row][col] > answer) answer = triangle[row][col];
        }
    }
    
    return answer;
}