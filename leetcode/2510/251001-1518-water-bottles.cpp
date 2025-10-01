class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {
        int ret = 0;
        int full_bottle = numBottles, empty_bottle = 0;
        while (full_bottle > 0) {
            ret += full_bottle;
            empty_bottle += full_bottle;
            full_bottle = empty_bottle / numExchange;
            empty_bottle = empty_bottle % numExchange;
        }
        return ret;
    }
};
