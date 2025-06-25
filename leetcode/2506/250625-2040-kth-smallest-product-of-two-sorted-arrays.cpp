class Solution {
    int findLowerBound(const vector<int> &v, const long long &val) {
        return findLowerBound(v.begin(), v.end(), val);
    }

    int findLowerBound(vector<int>::const_iterator v_begin, vector<int>::const_iterator v_end, const long long &val) {
        vector<int>::const_iterator v_start = v_begin;

        while (v_start < v_end) {
            vector<int>::const_iterator v_mid = v_start + (v_end - v_start) / 2;
            if (*v_mid < val) {
                v_start = v_mid;
                v_start++;
            } else {
                v_end = v_mid;
            }
        }
        return v_start - v_begin;
    }

    int findUpperBound(const vector<int> &v, const long long &val) {
        return findUpperBound(v.begin(), v.end(), val);
    }

    int findUpperBound(vector<int>::const_iterator v_begin, vector<int>::const_iterator v_end, const long long &val) {
        vector<int>::const_iterator v_start = v_begin;
        while (v_start < v_end) {
            vector<int>::const_iterator v_mid = v_start + (v_end - v_start) / 2;
            if (*v_mid <= val) {
                v_start = v_mid;
                v_start++;
            } else {
                v_end = v_mid;
            }
        }
        return v_start - v_begin;
    }

    long long findNegative(const vector<int> &nums1, const vector<int> &nums2, const int &idx1, const int &pos_idx1, const int &idx2, const int &pos_idx2, const long long k) {
        long long lp = -100'000L * 100'000 - 1, rp = 0;

        // cout << "Target k = " << k << endl;
        while (lp < rp) {
            long long mid = lp + (rp - lp) / 2;
            long long cnt = 0;

            // cout << "mid = " << mid << endl;
            // Examine nums1[..idx1] and nums2[pos_idx2..]
            for (int i = pos_idx2; i < nums2.size(); i++) {
                long long target = (mid - (nums2[i] - 1)) / nums2[i];
                int targetidx = findUpperBound(nums1.begin(), nums1.begin() + idx1, target);
                cnt += targetidx;
            }

            // Examine nums1[pos_idx1..] and nums2[..idx2]
            for (int i = pos_idx1; i < nums1.size(); i++) {
                long long target = (mid - (nums1[i] - 1)) / nums1[i];
                int targetidx = findUpperBound(nums2.begin(), nums2.begin() + idx2, target);
                cnt += targetidx;
            }

            // cout << "Result cnt = " << cnt << endl;

            if (cnt < k) {
                lp = mid + 1;
            } else {
                rp = mid;
            }
        }
        return lp;
    }

    long long findPositive(const vector<int> &nums1, const vector<int> &nums2, const int &idx1, const int &pos_idx1, const int &idx2, const int &pos_idx2, long long k) {
        long long lp = 0, rp = 100'000L * 100'000 + 1;
        // cout << "Target k = " << k << endl;

        while (lp < rp) {
            long long mid = (lp + rp) / 2;
            // cout << "\nmid become " << mid << endl;

            long long cnt = 0;
            // Examine nums1[pos_idx1..] and nums2[pos_idx2..]
            for (int i = pos_idx1; i < nums1.size(); i++) {
                long long targetval = mid / nums1[i];
                int targetidx = findUpperBound(nums2.begin() + pos_idx2, nums2.end(), targetval);
                // cout << "For target " << targetval << " and value = " << nums1[i] << ", found target idx = " << targetidx << endl;
                cnt += targetidx;
                // cout << "Added " << targetidx - idx2 << endl;
            }

            // Examine nums1[..idx1] and nums2[..idx2]
            for (int i = 0; i < idx1; i++) {
                long long targetval = mid / nums1[i];
                int targetidx = findLowerBound(nums2.begin(), nums2.begin() + idx2, targetval);
                cnt += idx2 - targetidx;
            }

            // cout << "Result cnt = " << cnt << endl;

            if (cnt < k) {
                lp = mid + 1;
            } else {
                rp = mid;
            }
        }
        return lp;
    }
public:
    long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2, long long k) {
        int idx1 = findLowerBound(nums1, 0), pos_idx1 = findUpperBound(nums1, 0);
        int idx2 = findLowerBound(nums2, 0), pos_idx2 = findUpperBound(nums2, 0);

        long long neg1 = idx1, zeros1 = pos_idx1 - idx1, pos1 = nums1.size() - pos_idx1;
        long long neg2 = idx2, zeros2 = pos_idx2 - idx2, pos2 = nums2.size() - pos_idx2;

        long long total = (long long)nums1.size() * nums2.size();
        long long totNegative = neg1 * pos2 + pos1 * neg2;
        long long totPositive = neg1 * neg2 + pos1 * pos2;
        long long totZero = total - totNegative - totPositive;

        // cout << "tot = " << totNegative << ", " << totZero << ", " << totPositive << endl;

        if (k <= totNegative) {
            return findNegative(nums1, nums2, idx1, pos_idx1, idx2, pos_idx2, k);
        } else if (k <= totNegative + totZero) {
            return 0;
        } else {
            return findPositive(nums1, nums2, idx1, pos_idx1, idx2, pos_idx2, k - totNegative - totZero);
        }
    }
};
