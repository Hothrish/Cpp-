struct trieNode{
    trieNode* x[2];
    int c;
    trieNode(){
        x[0]=NULL;
        x[1]=NULL;
        c=0;
    }
};
class Solution {
    trieNode* root;
public:
    int maximumStrongPairXor(vector<int>& nums) {
        int n=nums.size();
        sort(nums.begin(),nums.end());
        int l=0;
        int r=0;
        root=new trieNode();
        int ans=0;
        while(r<n){
            insert(nums[r]);
            while(2LL*nums[l]<nums[r]){
                remove(nums[l]);
                l++;
            }
            ans=max(ans,xor1(nums[r]));
            r++;
        }
        return ans;
    }
    void insert(int num){
        trieNode* a=root;
        for(int i=31;i>=0;i--){
            int j=(num>>i)&1;
            if(a->x[j]==NULL){
                a->x[j]=new trieNode();
            }
            a=a->x[j];
            a->c++;
        }
    }
    int xor1(int num){
        trieNode* a=root;
        int ans=0;
        for(int i=31;i>=0;i--){
            int j=(num>>i)&1;
            if(a->x[1-j] && a->x[1-j]->c>0){
                ans|=(1u<<i);
                a=a->x[1-j];
            }
            else if(a->x[j]->c>0 && a->x[j]){
                a=a->x[j];
            }
            else break;
        }
        return ans;
    }
    void remove(int num){
        trieNode* a=root;
        for(int i=31;i>=0;i--){
            int j=(num>>i)&1;
            a=a->x[j];
            a->c--;
        }
    }
};
