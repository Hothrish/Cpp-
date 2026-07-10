/*Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.

A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:

All the visited cells of the path are 0.
All the adjacent cells of the path are 8-directionally connected (i.e., they are different and they share an edge or a corner).
The length of a clear path is the number of visited cells of this path.*/
class Solution {
public:
vector<pair<int,int>>dir={{0,1},{1,0},{-1,0},{0,-1},{1,1},{1,-1},{-1,-1},{-1,1}};
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n=grid.size();
        if(grid[0][0]==1 || grid[n-1][n-1]==1) return -1;
        queue<pair<int,pair<int,int>>>q;
        q.push({1,{0,0}});
        int c=0;
        while(!q.empty()){
            int r=q.front().second.first;
            int c=q.front().second.second;
            int d=q.front().first;
            q.pop();
            if(r==n-1 && c==n-1){
                return d;
            }
            for(auto [i,j]:dir){
                int nr=r+i;
                int nc=c+j;
                if(nr>=0 && nr<n && nc>=0 && nc<n && grid[nr][nc]==0){
                    grid[nr][nc]=1;
                    q.push({d+1,{nr,nc}});
                }
            }
        }
        return -1;
    }
};
