class Solution {
    bool setCnt(int fruit_type[2], int cnt[2], const int &fruit) {
        for (int i = 0; i < 2; i++) {
            if (fruit_type[i] == -1) {
                fruit_type[i] = fruit; cnt[i] = 1; return true;
            } else if (fruit_type[i] == fruit) {
                cnt[i]++; return true;
            }
        }
        return false;
    }

    void unsetCnt(int fruit_type[2], int cnt[2], const int &fruit) {
        for (int i = 0; i < 2; i++) {
            if (fruit_type[i] == fruit) {
                cnt[i]--;
                if (cnt[i] == 0) fruit_type[i] = -1;
                return;
            }
        }
    }

public:
    int totalFruit(vector<int>& fruits) {
        int ans = 0;
        int cnt[2] = { 0 };
        int fruit_type[2] = { -1, -1 };

        for (int lp = 0, rp = 0; rp < fruits.size(); lp++) {
            while (rp < fruits.size()) {
                if (!setCnt(fruit_type, cnt, fruits[rp])) break;
                rp++;
            }
            ans = max(ans, rp - lp);
            unsetCnt(fruit_type, cnt, fruits[lp]);
        }
        return ans;
    }
};
