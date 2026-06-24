class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(2));

        dp[0][0] = 0;
        dp[0][1] = -prices[0];

        for (int i = 1; i < n; i++) {
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
            dp[i][1] = max(dp[i-1][1], -prices[i]);
        }

        return dp[n-1][0];
    }
};
//dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])  notholding stock
//dp[i][1] = max(dp[i-1][1], -prices[i])   holding stock
//space optimization
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int hold = -prices[0];
        int notHold = 0;

        for (int i = 1; i < prices.size(); i++) {
            notHold = max(notHold, hold + prices[i]);
            hold = max(hold, -prices[i]);
        }

        return notHold;
    }
};
