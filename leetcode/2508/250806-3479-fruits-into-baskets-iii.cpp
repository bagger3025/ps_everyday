struct seg_ele {
    int l;
    int r;
    int maxval;
};

class segTree {
private:
    vector<seg_ele> arr;

    void initTree(int idx, int l, int r, const vector<int> &vals) {
        if (l == r) {
            arr[idx] = {.l=l, .r=r, .maxval=vals[l]};
            return;
        }

        int mid = (l + r) / 2;
        initTree(idx * 2 + 1, l, mid, vals);
        initTree(idx * 2 + 2, mid + 1, r, vals);

        arr[idx] = {.l=l, .r=r, .maxval=max(arr[idx * 2 + 1].maxval, arr[idx * 2 + 2].maxval)};
    }

    int recMaxval(int idx, int l, int r) {
        if (l <= arr[idx].l && arr[idx].r <= r) return arr[idx].maxval;
        if (arr[idx].r < l || r < arr[idx].l) return -1;

        return max(recMaxval(idx * 2 + 1, l, r), recMaxval(idx * 2 + 2, l, r));
    }

    int recSetval(int idx, int x, int val) {
        if (arr[idx].r < x || x < arr[idx].l) return arr[idx].maxval;
        if (arr[idx].l == arr[idx].r) {
            arr[idx].maxval = val;
            return val;
        }

        int lval = recSetval(idx * 2 + 1, x, val);
        int rval = recSetval(idx * 2 + 2, x, val);
        return arr[idx].maxval = max(lval, rval);
    }

    int recLowerBound(int idx, int val) {
        if (arr[idx].maxval < val) return arr[idx].r + 1;
        if (arr[idx].l == arr[idx].r) return arr[idx].l;
        int ret = recLowerBound(idx * 2 + 1, val);
        if (ret != arr[idx * 2 + 1].r + 1) return ret;

        return recLowerBound(idx * 2 + 2, val);
    }

public:
    segTree(const vector<int> &vals): arr(4 * vals.size()) {
        initTree(0, 0, vals.size() - 1, vals);
    }

    int getMaxval(int r) {
        return recMaxval(0, 0, r);
    }

    int getLowerBound(int val) {
        return recLowerBound(0, val);
    }

    void setMaxval(int x, int val) {
        recSetval(0, x, val);
    }
};

class Solution {
    void update(vector<int> &fenwick, int idx, int val) {
        if (idx >= fenwick.size()) return;
        fenwick[idx] = max(fenwick[idx], val);
        return update(fenwick, idx + (idx & (-idx)), val);
    }
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        segTree st(baskets);

        int ans = 0;
        for (int i = 0; i < fruits.size(); i++) {
            int idx = st.getLowerBound(fruits[i]);
            if (idx >= baskets.size()) {
                ans++;
                continue;
            }
            st.setMaxval(idx, -1);
        }
        return ans;
    }
};
