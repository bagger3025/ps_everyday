class Solution {
public:
    long long minTime(vector<int>& skill, vector<int>& mana) {
        long long ret = 0;
        for (int i = 1; i < mana.size(); i++) {
            long long delayed = 0;
            long long prev_start_at = 0, start_at = 0;
            for (int j = 0; j < skill.size(); j++) {
                long long prev_end_at = prev_start_at + static_cast<long long>(skill[j]) * mana[i - 1];
                long long delta = max(0LL, prev_end_at - start_at);
                start_at += delta; delayed += delta;

                prev_start_at = prev_end_at;
                start_at += static_cast<long long>(skill[j]) * mana[i];
            }
            cout << delayed << endl;
            ret += delayed;
        }
        for (auto s: skill) {
            ret += static_cast<long long>(s) * mana.back();
        }
        return ret;
    }
};
