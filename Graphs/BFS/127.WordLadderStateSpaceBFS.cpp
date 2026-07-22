/*
A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:

Every adjacent pair of words differs by a single letter.
Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
sk == endWord
Given two words, beginWord and endWord, and a dictionary wordList, return the number of words in the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.

 

Example 1:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", which is 5 words long.
*/
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string>words(wordList.begin(),wordList.end());
        queue<pair<string,int>>q;
        int n=size(beginWord);
        q.push({beginWord,1});
        unordered_set<string>s;
        s.insert(beginWord);
        int ans=1;
        while(!q.empty()){
            auto [t,c]=q.front();q.pop();
            if(t==endWord){
                cout<<ans;
                return c;
            }
            for(int i=0;i<n;i++){
                string x=t;
                for(char ch='a';ch<='z';ch++){
                    x[i]=ch;
                    if(words.count(x) && !s.count(x)){
                        q.push({x,c+1});
                        s.insert(x);
                    }
                }
            }
            ans++;
        }
        return 0;
    }
};
