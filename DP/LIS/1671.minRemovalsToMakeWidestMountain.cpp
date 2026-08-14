/*
You may recall that an array arr is a mountain array if and only if:

arr.length >= 3
There exists some index i (0-indexed) with 0 < i < arr.length - 1 such that:
arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
Given an integer array nums​​​, return the minimum number of elements to remove to make nums​​​ a mountain array.
*/
class Solution {
public:
    int minimumMountainRemovals(vector<int>& nums) {
        int n = nums.size();
        vector<int> left(n),right(n);
        vector<int> tail;
        for(int i=0;i<n;++i){
            auto it = lower_bound(tail.begin(),tail.end(),nums[i]);
            if(it == tail.end()){
                tail.push_back(nums[i]);
                left[i] = tail.size();
            }
            else{
                *it = nums[i];
                left[i] = distance(tail.begin(),it) + 1;
            }
        }
        tail.clear();
        for(int i=n-1;i>=0;--i){
            auto it = lower_bound(tail.begin(),tail.end(),nums[i]);
            if(it == tail.end()){
                tail.push_back(nums[i]);
                right[i] = tail.size();
            }
            else{
                *it = nums[i];
                right[i] = distance(tail.begin(),it) + 1;
            }
        }
        int ans = 0;
        for(int i=0;i<n;++i){
            if(left[i]==1 || right[i] == 1) continue;
            ans = max(ans,left[i]+right[i]-1);
        }
        return n-ans;
    }
};
