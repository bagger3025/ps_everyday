class SegTree {
    struct segtree_ele {
        int from;
        int to;
        long long val;
    };

    vector<segtree_ele> arr;
    int n;

    void initTree(int idx, int from, int to) {
        if (from == to) {
            arr[idx] = {.from=from, .to=to, .val=0};
            return;
        }
        int midval = (from + to) / 2;
        initTree(idx * 2 + 1, from, midval);
        initTree(idx * 2 + 2, midval + 1, to);
        arr[idx] = {.from=from, .to=to, .val=0};
    }

    long long getSum(int idx, int from, int to) {
        if (to < arr[idx].from || arr[idx].to < from) return 0;
        if (from <= arr[idx].from && arr[idx].to <= to) return arr[idx].val;

        long long leftsum = getSum(idx * 2 + 1, from, to);
        long long rightsum = getSum(idx * 2 + 2, from, to);
        return leftsum + rightsum;
    }

    void setValRec(int idx, int k, long long v) {
        if (k < arr[idx].from || arr[idx].to < k) return;
        if (arr[idx].from == k && arr[idx].to == k) {
            arr[idx].val = v;
            return;
        }
        setValRec(idx * 2 + 1, k, v);
        setValRec(idx * 2 + 2, k, v);
        arr[idx].val = arr[idx * 2 + 1].val + arr[idx * 2 + 2].val;
    }

public:
    SegTree(int n): arr(4 * n), n(n) {
        initTree(0, 0, n - 1);
    }

    long long getSumFrom(int idx) {
        return getSum(0, idx, n - 1);
    }

    void setVal(int k, int v) {
        setValRec(0, k, v);
    }
};

class Solution {
public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        const int n = nums1.size();
        vector<int> idxes(n);
        for (int i = 0; i < n; i++) {
            idxes[nums2[i]] = i;
        }

        vector<int> reorders(n);
        for (int i = 0; i < n; i++) {
            reorders[i] = idxes[nums1[i]];
        }

        vector<long long> dp(n);
        SegTree sg_tree(n);

        for (int i = n - 1; i >= 0; i--) {
            long long cnt = sg_tree.getSumFrom(reorders[i]);
            sg_tree.setVal(reorders[i], 1);
            
            dp[i] = cnt;
        }

        long long ans = 0;
        SegTree second_sgtree(n);
        for (int i = n - 1; i >= 0; i--) {
            long long cnt = second_sgtree.getSumFrom(reorders[i]);
            second_sgtree.setVal(reorders[i], dp[i]);

            ans += cnt;
        }

        return ans;
    }

};
