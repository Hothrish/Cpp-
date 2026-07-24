#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> openLockPath(vector<string>& deadends, string target) {
        unordered_set<string> dead(deadends.begin(), deadends.end());
        if (dead.count("0000")) return {};
        if (target == "0000") return {"0000"};

        queue<string> q;
        q.push("0000");
        unordered_set<string> visited;
        visited.insert("0000");

        unordered_map<string,string> parent; // child -> parent

        while (!q.empty()) {
            string cur = q.front();
            q.pop();

            if (cur == target) {
                // reconstruct path
                vector<string> path;
                for (string at = target; !at.empty(); at = parent[at]) {
                    path.push_back(at);
                }
                reverse(path.begin(), path.end());
                return path;
            }

            for (int i = 0; i < 4; i++) {
                char c = cur[i];

                // forward turn
                cur[i] = (c == '9' ? '0' : c + 1);
                if (!dead.count(cur) && !visited.count(cur)) {
                    q.push(cur);
                    visited.insert(cur);
                    parent[cur] = q.front(); // store parent
                }
                cur[i] = c;

                // backward turn
                cur[i] = (c == '0' ? '9' : c - 1);
                if (!dead.count(cur) && !visited.count(cur)) {
                    q.push(cur);
                    visited.insert(cur);
                    parent[cur] = q.front();
                }
                cur[i] = c;
            }
        }
        return {}; // no path
    }
};
/*You have a lock in front of you with 4 circular wheels. Each wheel has 10 slots: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'. The wheels can rotate freely and wrap around: for example we can turn '9' to be '0', or '0' to be '9'. Each move consists of turning one wheel one slot.

The lock initially starts at '0000', a string representing the state of the 4 wheels.

You are given a list of deadends dead ends, meaning if the lock displays any of these codes, the wheels of the lock will stop turning and you will be unable to open it.

Given a target representing the value of the wheels that will unlock the lock, return the minimum total number of turns required to open the lock, or -1 if it is impossible.

 */
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        if(target=="0000"){
            return 0;
        }
        vector<int> state(10000);
        vector<int> q1, q2;
        for(auto& str:deadends){
            state[stoi(str)]=-1;
            if(stoi(str)==0){
                return -1;
            }
        }
        q1.push_back(0), q2.push_back(stoi(target));
        state[0]=1, state[stoi(target)]=2;
        int d=0;
        while(!q1.empty() && !q2.empty()){
            if(q1.size()>q2.size()){
                swap(q1, q2);
            }                
            vector<int> tmpq;
            for(int curr:q1){    
                int st=state[curr];
                int tmp=curr, base=1;
                for(int i=0;i<4;i++){
                    int up, down;
                    if(tmp%10==9){
                        up=curr-9*base;
                    }
                    else up=curr+base;
                    if(tmp%10==0){
                        down=curr+9*base;
                    }
                    else down=curr-base;
                    if(state[up]!=-1){
                        if(!state[up]){
                            state[up]=st;
                            tmpq.push_back(up);
                        }
                        else if(state[up]!=st) {
                            return d+1;
                        }
                    }
                    if(state[down]!=-1){
                        if(!state[down]){
                            state[down]=st;
                            tmpq.push_back(down);
                        }
                        else if(state[down]!=st) {
                            return d+1;
                        }
                    }
                    tmp/=10;
                    base*=10;
                }
            }
            q1=tmpq;
            d++;
        }
        return -1;
    }
};

