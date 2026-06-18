class Solution {
public:
vector<vector<int>>adj;
vector<int>subsize;
vector<int>res;
vector<int>dp;
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        subsize.resize(n);
        adj.resize(n);
        res.resize(n);
        dp.resize(n);
        for(auto& e:edges){
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        dfs1(0,-1);
        res[0]=dp[0];
        dfs2(0,-1);
        return res;
    }
    void dfs1(int u,int p){
        subsize[u]=1;
        dp[u]=0;
        for(int v:adj[u]){
            if(v==p) continue;
            dfs1(v,u);
            subsize[u]+=subsize[v];
            dp[u]+=dp[v]+subsize[v];
        }
    }
    void dfs2(int u,int p){
        for(int v:adj[u]){
            if(v==p) continue;
            res[v]=res[u]-subsize[v]+adj.size()-subsize[v];
            dfs2(v,u);
        }
    }
};
