/*Given the root of a binary tree, calculate the vertical order traversal of the binary tree.

For each node at position (row, col), its left and right children will be at positions (row + 1, col - 1) and (row + 1, col + 1) respectively. The root of the tree is at (0, 0).

The vertical order traversal of a binary tree is a list of top-to-bottom orderings for each column index starting from the leftmost column and ending on the rightmost column. There may be multiple nodes in the same row and same column. In such a case, sort these nodes by their values.

Return the vertical order traversal of the binary tree.*/
class Solution {
public:
int a,b;
map<int,vector<pair<int,int>>>mp;
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        if(!root) return {};
        vector<vector<int>>ans;
        a=INT_MAX;
        b=INT_MIN;
        dfs(root,0,0);
        for(int i=a;i<=b;i++){
            sort(mp[i].begin(),mp[i].end());
            vector<int>c;
            for(auto p:mp[i]){
                c.push_back(p.second);
            }
            ans.push_back(c);
        }
        return ans;
    }
    void dfs(TreeNode*node,int x,int y){
        if(!node){
            return;
        }
        a=min(a,y);
        b=max(b,y);
        mp[y].push_back({x,node->val}); 
        if(node->left){
            dfs(node->left,x+1,y-1);
        }
        if(node->right){
            dfs(node->right,x+1,y+1);
        }   
    }
};
