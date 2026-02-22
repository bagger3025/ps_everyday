impl Solution {
    pub fn binary_gap(mut n: i32) -> i32 {
        let mut ret = 0;

        while n % 2 != 1 {
            n >>= 1;
        }

        loop {
            n >>= 1;
            if n == 0 { break ret; }

            let mut t = 1;
            while n % 2 != 1 {
                n >>= 1; t += 1;
            }

            ret = if t > ret { t } else { ret };
        }
    }
}
