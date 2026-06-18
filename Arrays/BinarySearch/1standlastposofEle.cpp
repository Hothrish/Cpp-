class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int n=nums.size();
        if(n==0) return{-1,-1};
        int l=0;
        int r=n-1;
        while(l<=r){
            int mid=l+((r-l)/2);
            if(nums[mid]<target){
                l=mid+1;
            }
            else if(nums[mid]>target){
                r=mid-1;
            }
            else{
                int left=mid;
                int right=mid;
                while(left-1>=0 && nums[left-1]==target){
                    left--;
                }
                while(right+1<n && nums[right+1]==target){
                    right++;
                }
                return{left,right};
            }
        }
        return {-1,-1};
    }
};
