/*There are n servers numbered from 0 to n - 1 connected by undirected server-to-server connections forming a network where connections[i] = [ai, bi] represents a connection between servers ai and bi. Any server can reach other servers directly or indirectly through the network.

A critical connection is a connection that, if removed, will make some servers unable to reach some other server.

Return all critical connections in the network in any order.*/
class Solution {
public:
vector<int>tin;
vector<int>low;
vector<bool>vis;
vector<vector<int>>adj;
int timer;
void dfs(int u,int par,vector<vector<int>>&ans){
    vis[u]=true;
    low[u]=tin[u]=timer++;
    for(auto v:adj[u]){
        if(v==par) continue; // immediate back edge is not a back edge kadha
        if(vis[v]){
            low[u]=min(low[u],tin[v]); //ippudu back edge aythe connected components nee satisfy chesthadhi inka earliest time thisko anna,ante ippude subtree cycle from ayidhi so no bridge
        }
        else{
            dfs(v,u,ans);//kindha ki ellu
            low[u]=min(low[u],low[v]);//sub tree where back edge is connected to ancistor payki pampu value 
            if(low[v]>tin[u]){
                ans.push_back({u,v});//kakunte back edge ee kadha kaka
            }
        }
    }
}
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        adj.assign(n,{});
        tin.resize(n);
        low.resize(n);
        vis.assign(n,false);
        timer=0;
        for(auto c:connections){
            adj[c[0]].push_back(c[1]);
            adj[c[1]].push_back(c[0]);
        }
        vector<vector<int>>ans;
        dfs(0,-1,ans);//anni connected annaru so ekkada nunche ayna start cheyochu,disconnected aythe loop esi ani check cheyali
        return ans;
    }
};
