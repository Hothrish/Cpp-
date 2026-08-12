//2DAGS one dag for forward ,another for 2 iteration and backward
//The first pass handles paths whose useful movement is:
//up + left
//The second handles:
//down + right
/*Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.
The distance between two cells sharing a common edge is 1.*/
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {

        int m = mat.size();
        int n = mat[0].size();

        const int INF = 1e9;

        vector<vector<int>> dp(m, vector<int>(n, INF));

        // First DAG:
        // dependencies = up, left
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {

                if(mat[i][j] == 0) {
                    dp[i][j] = 0;
                }
                else {

                    if(i > 0)
                        dp[i][j] = min(
                            dp[i][j],
                            dp[i-1][j] + 1
                        );

                    if(j > 0)
                        dp[i][j] = min(
                            dp[i][j],
                            dp[i][j-1] + 1
                        );
                }
            }
        }

        // Second DAG:
        // dependencies = down, right
        for(int i = m - 1; i >= 0; i--) {
            for(int j = n - 1; j >= 0; j--) {

                if(i + 1 < m)
                    dp[i][j] = min(
                        dp[i][j],
                        dp[i+1][j] + 1
                    );

                if(j + 1 < n)
                    dp[i][j] = min(
                        dp[i][j],
                        dp[i][j+1] + 1
                    );
            }
        }

        return dp;
    }
};
