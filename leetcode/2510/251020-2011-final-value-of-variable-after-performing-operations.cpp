class Solution {
public:
    int finalValueAfterOperations(vector<string>& operations) {
        int x = 0;
        for (auto &op: operations) {
            switch (op[1]) {
                case '+': x++; break;
                case '-': x--; break;
            }
        }
        return x;
    }
};
