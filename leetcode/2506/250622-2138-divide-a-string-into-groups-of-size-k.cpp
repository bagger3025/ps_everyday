class Solution {
public:
    vector<string> divideString(string s, int k, char fill) {
        vector<string> ret;
        for (int i = 0; i < s.size(); i += k) {
            string ele = s.substr(i, k);
            while (ele.size() != k) {
                ele += fill;
            }
            ret.push_back(ele);
        }
        return ret;
    }
};
