class Solution {
    vector<int> arr;

    inline bool is_set(const int &n, const int &idx) {
        return (n & (1 << idx));
    }

    void init_arr() {
        arr = vector<int>(30);

        arr[0] = 1;
        for (int i = 1; i < arr.size(); i++) {
            arr[i] = arr[i - 1] + 1 + arr[i - 1];
        }        
    }

    int recOperations(int n, int fromidx) {
        int i = fromidx;
        while (i >= 0 && !is_set(n, i)) {
            i--;
        }
        if (i == -1) return 0;
        if (i == 0) return 1;

        n ^= 1 << i;
        int j = i - 1;
        while (j >= 0 && !is_set(n, j)) {
            j--;
        }
        int ans = 0;
        // ith bit = 1, (i - 1)..(j + 1)th bit = 0, jth bit = 1
        if (j >= 0) {
            n ^= 1 << j;
            ans += recOperations(n, j - 1);
        }
        while (j + 1 < i) {
            ans += 1; // make (j+1)th bit to 1
            if (j >= 0) {
                ans += arr[j]; // make jth bit to 0
            }
            j++;
        }

        // current: ith bit = 1, (i - 1)th bit = 1
        ans += 1; // for making ith bit to 0
        ans += arr[i - 1]; // for making (i - 1)th bit to 0
        return ans;
    }
public:
    int minimumOneBitOperations(int n) {
        init_arr();
        return recOperations(n, 29);
    }
};
