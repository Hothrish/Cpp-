/*You are given an m x n grid where each cell can have one of three values:

0 representing an empty cell,
1 representing a fresh orange, or
2 representing a rotten orange.
Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.*/
class Solution {
public:
vector<pair<int,int>>dir={{1,0},{0,1},{-1,0},{0,-1}};
    int orangesRotting(vector<vector<int>>& grid) {
        int m=grid.size();
        int n=grid[0].size();
        queue<tuple<int,int,int>>q;
        int t1=0;
        int t2=0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==2){
                    q.push({i,j,0});
                    t1++;
                }
                else if(grid[i][j]==1){
                    t2++;
                }
            }
        }
        if(t2==0) return 0;
        if(t1==0) return -1;
        int x=0;
        while(!q.empty()){
            auto [r,c,t]=q.front();q.pop();
            x=max(x,t);
            for(auto [dr,dc]:dir){
                int nr=r+dr;
                int nc=c+dc;
                if(nr<0 || nr>=m || nc<0 || nc>=n){
                    continue;
                }
                else if(grid[nr][nc]==1){
                    grid[nr][nc]=2;
                    q.push({nr,nc,t+1});
                    t2--;
                }
            }
        }
        return (t2==0)?x:-1;
    }
};
