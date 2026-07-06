// Binary Exponentiation
// Time: O(log exp)

long long fastPower(long long base, long long exp) {
    long long res = 1;
    while (exp) {
        if (exp & 1)
            res *= base;
        base *= base;
        exp >>= 1;
    }
    return res;
}

// Binary Exponentiation (Mod)
// Time: O(log exp)

long long modPower(long long base, long long exp, long long mod) {
    base %= mod;
    long long res = 1 % mod;
    while (exp) {
        if (exp & 1)
            res = (__int128)res * base % mod;
        base = (__int128)base * base % mod;
        exp >>= 1;
    }
    return res;
}
