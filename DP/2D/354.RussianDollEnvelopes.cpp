/*You are given a 2D array of integers envelopes where envelopes[i] = [wi, hi] represents the width and the height of an envelope.

One envelope can fit into another if and only if both the width and height of one envelope are greater than the other envelope's width and height.

Return the maximum number of envelopes you can Russian doll (i.e., put one inside the other).

Note: You cannot rotate an envelope.*/
/*its actually a LIS problem but here dp is not used binary search is used*/
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int m=envelopes.size();
        if(m==0) return 0;
        sort(envelopes.begin(), envelopes.end(),[](vector<int>&a, vector<int>&b){
                if(a[0]==b[0])
                    return a[1]>b[1];
                return a[0]<b[0];
            });
        vector<int>x;
        for(int i=0;i<m;i++){
            x.push_back(envelopes[i][1]);
        }
        vector<int>a;
        for(int n:x){
            auto it=lower_bound(a.begin(),a.end(),n);
            if(it==a.end()){
                a.push_back(n);
            }
            else{
                *it=n;
            }
        }
        return a.size();
    }
};
