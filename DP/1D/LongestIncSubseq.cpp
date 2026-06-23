class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> tail;
        for (int x : nums) {
            auto it = lower_bound(tail.begin(), tail.end(), x);
            if (it == tail.end())
                tail.push_back(x);
            else
                *it = x;
        }
        return tail.size();
    }
};
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n=nums.size();
        if(n==1) return 1;
        vector<int>dp(n,1);
        int x=1;
        for(int i=1;i<n;i++){
            for(int j=0;j<i;j++){
                if(nums[i]>nums[j]){
                    dp[i]=max(dp[i],dp[j]+1);
                }
            }
            x=max(dp[i],x);
        }
        return x;
    }
};
