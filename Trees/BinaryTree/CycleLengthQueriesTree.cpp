/*You are given an integer n. There is a complete binary tree with 2n - 1 nodes. The root of that tree is the node with the value 1, and every node with a value val in the range [1, 2n - 1 - 1] has two children where:

The left node has the value 2 * val, and
The right node has the value 2 * val + 1.
You are also given a 2D integer array queries of length m, where queries[i] = [ai, bi]. For each query, solve the following problem:

Add an edge between the nodes with values ai and bi.
Find the length of the cycle in the graph.
Remove the added edge between nodes with values ai and bi.
Note that:

A cycle is a path that starts and ends at the same node, and each edge in the path is visited only once.
The length of a cycle is the number of edges visited in the cycle.
There could be multiple edges between two nodes in the tree after adding the edge of the query.
Return an array answer of length m where answer[i] is the answer to the ith query.*/
struct treeNode{
    treeNode* left;
    treeNode* right;
    int val;
    treeNode(){
        left=NULL;
        right=NULL;
        val=0;
    }
};
class Solution {

public:
treeNode* root;
    vector<int> cycleLengthQueries(int n, vector<vector<int>>& queries) {
        root=new treeNode();
        root->val=1;
        queue<treeNode*>q;
        q.push(root);
        while(!q.empty() && n>0){
            int m=q.size();
            n--;
            for(int i=0;i<m;i++){
                auto node=q.front();q.pop();
                node->left=new treeNode();
                node->left->val=2*node->val;
                node->right=new treeNode();
                node->right->val=2*node->val+1;
                q.push(node->left);
                q.push(node->right);
            }
        }
        vector<int>y;
        for(auto q:queries){
            y.push_back(dfs(root,q[0],0)+dfs(root,q[1],0)-2*dfs(root,lca(root,q[0],q[1]),0)+1);
        }
        return y;
    }
    int dfs(treeNode* x, int a, int i) {
         if (!x) return -1;
        if (x->val==a)
            return i;
        int left=dfs(x->left,a,i+1);
        if (left!=-1)
            return left;
        return dfs(x->right,a,i+1);
    }
    int lca(treeNode* root,int p,int q) {
        if(!root){
            return -1;
        }
        if(root->val==p|| root->val==q)
            return root->val;
        int left=lca(root->left,p,q);
        int right=lca(root->right,p,q);
        if (left!=-1 && right!=-1)
            return root->val;
        return (left!=-1)?left:right;
    }
};
