const int LIMIT = 31'623; // sqrt(1e9)

class Solution {
public:
    int maximumLength(vector<int>& nums) {
        bitset<LIMIT> freq1, freq2, sqset;

        int ones = 0, minv = LIMIT, maxv = 0;
        for (int v : nums) {
            if (v == 1)
                ones++;
            else if (v < LIMIT) {
                if (!freq1[v]) {
                    freq1[v] = 1;
                } else {
                    freq2[v] = 1;
                    minv = min(minv, v);
                    maxv = max(maxv, v);
                }
            } else {
                int r = sqrt(v);
                if (r * r == v)
                    sqset[r] = 1;
            }
        }

        int maxlen = max(1, ones - (1 - ones & 1));

        auto get = [&](long long v) -> int {
            if (v < LIMIT)
                return freq1[v] + freq2[v];
            int r = sqrt(v);
            return r * r == v && r < LIMIT && sqset[r];
        };

        for (int i = minv; i <= maxv; i++) {
            if (freq2[i]) {
                int x = i;
                int currlen = 0, f = get(x);
                while (f > 1) {
                    currlen++;
                    x *= x;
                    f = get(x);
                }
                maxlen = max(maxlen, 2 * (currlen + f) - 1);
            }
        }
        return maxlen;
    }
};
