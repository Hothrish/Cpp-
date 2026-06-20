class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        if(restrictions.size()==0) return n-1;
        restrictions.push_back({1,0});
        sort(restrictions.begin(),restrictions.end());
        int m=restrictions.size();
        int x=0;
        for(int i=1;i<m;i++){
            restrictions[i][1]=min(restrictions[i][1],restrictions[i-1][1]+(restrictions[i][0]-restrictions[i-1][0]));
        }
        for(int i=m-1;i>0;i--){
             restrictions[i-1][1]=min(restrictions[i-1][1],restrictions[i][1]+(restrictions[i][0]-restrictions[i-1][0]));
        }
        for(int i=1;i<m;i++){
            x=max(x,(restrictions[i][0]-restrictions[i-1][0]+restrictions[i][1]+restrictions[i-1][1])/2);
        }
        if(n>restrictions[m-1][0]){
            x=max(n-restrictions[m-1][0]+restrictions[m-1][1],x);
        }
        return x;
    }
};
