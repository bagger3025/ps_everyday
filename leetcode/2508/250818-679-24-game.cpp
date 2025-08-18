int int_abs(int a) {
    return a > 0 ? a : -a;
}

int gcd(int a, int b) {
    if (a < b) return gcd(b, a);
    if (b == 0) return a;
    if (b == 1) return 1;
    return gcd(b, a % b);
}

struct Rational {
    int upper;
    int lower;

    Rational(const int &upper = 1, const int &lower = 1) {
        this->upper = upper; this->lower = lower;
    }

    Rational operator+(const Rational &other) const {
        return Rational(this->upper * other.lower + this->lower * other.upper, this->lower * other.lower);
    }

    Rational operator-(const Rational &other) const {
        return Rational(this->upper * other.lower - other.upper * this->lower, this->lower * other.lower);
    }

    Rational operator*(const Rational &other) const {
        return Rational(this->upper * other.upper, this->lower * other.lower);
    }

    Rational operator/(const Rational &other) const {
        return Rational(this->upper * other.lower, this->lower * other.upper);
    }

    bool operator==(const int &other) const {
        const int g = gcd(int_abs(this->upper), int_abs(this->lower));
        if (g == 0) return false;
        const int upper = this->upper / g, lower = this->lower / g;
        if (lower != 1) return false;
        return upper == other;
    }
};

class Solution {
    void print_rs(Rational rs[4], const int rs_idx) {
        cout << rs_idx << " / " << endl;
        for (int i = 0; i < rs_idx; i++) {
            cout << "[upper=" << rs[i].upper << ", lower=" << rs[i].lower << "] ";
        }
        cout << endl;
    }

    bool recJudge(const vector<int> &cards, vector<bool> &visited, int idx, Rational rs[4], int rs_idx) {
        if (idx == cards.size() && rs_idx == 1) {
            return rs[0] == 24;
        }

        if (rs_idx != 1) {
            const Rational rhs = rs[--rs_idx];
            const Rational lhs = rs[--rs_idx];

            bool ret = false;

            rs[rs_idx] = lhs + rhs;
            ret = recJudge(cards, visited, idx, rs, rs_idx + 1);
            if (ret) return true;

            rs[rs_idx] = lhs - rhs;
            ret = recJudge(cards, visited, idx, rs, rs_idx + 1);
            if (ret) return true;

            rs[rs_idx] = lhs * rhs;
            ret = recJudge(cards, visited, idx, rs, rs_idx + 1);
            if (ret) return true;

            rs[rs_idx] = lhs / rhs;
            ret = recJudge(cards, visited, idx, rs, rs_idx + 1);
            if (ret) return true;

            rs[rs_idx++] = lhs;
            rs[rs_idx++] = rhs;
        }
        for (int i = 0; i < cards.size(); i++) {
            if (visited[i]) continue;
            visited[i] = true;

            rs[rs_idx] = Rational(cards[i], 1);
            bool ret = recJudge(cards, visited, idx + 1, rs, rs_idx + 1);
            if (ret) return true;

            visited[i] = false;
        }
        return false;
    }
public:
    bool judgePoint24(vector<int>& cards) {
        vector<bool> visited(cards.size(), false);
        Rational rs[4];
        for (int i = 0; i < 4; i++) {
            visited[i] = true;
            rs[0] = Rational(cards[i], 1);
            bool ret = recJudge(cards, visited, 1, rs, 1);
            if (ret) return true;
            visited[i] = false;
        }
        return false;
    }
};
