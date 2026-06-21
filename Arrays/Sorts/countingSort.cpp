class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        int m=0;
        for(int c:costs){
            m=max(c,m);
        }
        vector<int>x(m+1,0);
        for(int c:costs){
            x[c]++;
        }
        int result=0;
        for(int i=1;i<=m;++i){
            if(x[i]>0){
                int c1=min(x[i],coins/i);
                result+=c1;
                coins-=c1*i;
                if(c1==0) break;
            }
        }
        return result;
    }
};
