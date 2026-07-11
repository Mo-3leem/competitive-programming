// ================= Power & Modular Arithmetic =================
// Time: O(log exp)
long long fastPower(long long base, long long exp) {
    long long res = 1;
    while (exp) {
        if (exp & 1) res *= base;
        base *= base;
        exp >>= 1;
    }
    return res;
}

// Time: O(1)
inline long long mulMod(long long a, long long b, long long mod) {
    return (__int128)((a % mod + mod) % mod) *
           ((b % mod + mod) % mod) % mod;
}

// Time: O(log exp)
long long modPower(long long base, long long exp, long long mod) {
    base = (base % mod + mod) % mod;
    long long res = 1 % mod;
    while (exp) {
        if (exp & 1) res = mulMod(res, base, mod);
        base = mulMod(base, base, mod);
        exp >>= 1;
    }
    return res;
}

// Time: O(log mod)
inline long long modInverse(long long a, long long mod) {
    return modPower(a, mod - 2, mod);
}

// Time: O(log mod)
inline long long divMod(long long a, long long b, long long mod) {
    return mulMod(a, modInverse(b, mod), mod);
}
