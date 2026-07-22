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
