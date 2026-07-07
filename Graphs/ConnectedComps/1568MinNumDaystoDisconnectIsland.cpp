/*You are given an m x n binary grid grid where 1 represents land and 0 represents water. An island is a maximal 4-directionally (horizontal or vertical) connected group of 1's.

The grid is said to be connected if we have exactly one island, otherwise is said disconnected.

In one day, we are allowed to change any single land cell (1) into a water cell (0).

Return the minimum number of days to disconnect the grid.*/
class Solution {
public:
vector<vector<bool>>vis;
int timer;
vector<vector<int>>low;
vector<vector<int>>tin;
vector<pair<int,int>>dir={{1,0},{0,1},{-1,0},{0,-1}};
int n,m;
bool t;
int l;
void dfs(vector<vector<int>>& g,int parx,int pary,int i,int j){
    if(g[i][j]==0) return;
    vis[i][j]=true;
    tin[i][j]=low[i][j]=++timer;
    int c=0;
    for(auto [dx,dy]:dir){
        int nx=i+dx;
        int ny=j+dy;
        if(nx<0 || ny<0 || nx>=m || ny>=n){
            continue;
        }
        if(g[nx][ny]==0||(nx==parx&&ny==pary)){
            continue;
        }
        if(vis[nx][ny]) low[i][j]=min(low[i][j],tin[nx][ny]);
        else{
            dfs(g,i,j,nx,ny);
            low[i][j]=min(low[i][j],low[nx][ny]);
            if((parx!=-1 && pary!=-1)&& low[nx][ny]>=tin[i][j]){
                t=true;
            }
            c++;
        }
    }
    if(parx==-1 && pary==-1 && c>1){
        t=true;
    }
}
void dfs1(vector<vector<int>>&g,int i,int j){
    l++;
    vis[i][j]=true;
    for(auto [dx,dy]:dir){
        int nx=i+dx;
        int ny=j+dy;
        if(nx<0 || ny<0 || nx>=m || ny>=n) continue;
        if(g[nx][ny]==0 || vis[nx][ny]) continue;
        dfs1(g,nx,ny);
    }
}
    int minDays(vector<vector<int>>& grid) {
        m=grid.size();
        n=grid[0].size();
        t=false;
        timer=0;
        vis.assign(m,vector<bool>(n,false));
        int c=0;
        l=0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==1 && !vis[i][j]){
                    dfs1(grid,i,j);
                    c++;
                }
            }
        }
        if(l==1) return 1;
        if(c==0 || c>1) return 0;
        vis.assign(m,vector<bool>(n,false));
        low.resize(m,vector<int>(n,0));
        tin.resize(m,vector<int>(n,0));
        bool x=false;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==1 && !vis[i][j]){
                    dfs(grid,-1,-1,i,j);
                    x=true;
                    break;
                }
            }
            if(x) break;
        }
        if(t) return 1;
        return 2;

    }
};
