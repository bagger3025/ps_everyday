class FindSumPairs {
    unordered_map<int, int> um;
    vector<int> nums1, nums2;
public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2): nums1(nums1), nums2(nums2) {
        for (const auto &n: nums2) {
            um[n]++;
        }
    }
    
    void add(int index, int val) {
        um[nums2[index]]--;
        nums2[index] += val;
        um[nums2[index]]++;
    }
    
    int count(int tot) {
        int ret = 0;
        for (int i = 0; i < nums1.size(); i++) {
            if (nums1[i] >= tot) continue;
            ret += um[tot - nums1[i]];
        }
        return ret;
    }
};

/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */
