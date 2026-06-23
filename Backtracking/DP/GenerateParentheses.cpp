class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<vector<string>>dp(n + 1);
        dp[0]={""};
        for (int i=1;i<=n;i++) {
            for (int j=0;j<i;j++) {
                for (string&l:dp[j]) {
                    for (string& r:dp[i-1-j]) {
                        dp[i].push_back("("+l+")"+r);
                    }
                }
            }
        }
        return dp[n];
    }
};
class Solution {
public:
vector<string>s;
    void dfs(int n,string x,int i,int j){
        if(x.size()==n*2){
            s.push_back(x);
            return;
        }
        if(i<n){
            x.push_back('(');
            dfs(n,x,i+1,j);
            x.pop_back();
        }
        if(j<i){
            x.push_back(')');
            dfs(n,x,i,j+1);
            x.pop_back();
        }
    }
    vector<string> generateParenthesis(int n) {
        string x;
        dfs(n,x,0,0);
        return s;
    }

};
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string>s;
        dfs(n,s,"(",1);
        return s;
    }
    void dfs(int n,vector<string>&s,string x,int j){
        if(j<0 ||x.size()>n*2) return;
        if(x.size()==n*2 && j==0){
            s.push_back(x);
            return;
        }
        dfs(n,s,x+'(',j+1);
        dfs(n,s,x+')',j-1);
    }
};
