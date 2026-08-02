using ll = long long;

const int MOD = 1e9 + 7;
const int MAX = 2e6 + 5;          // For factorials
const int NCR_MAX = 5000;         // Adjust according to memory

ll fact[MAX], invFact[MAX];
ll C[NCR_MAX + 1][NCR_MAX + 1];

//==================================================
// Fast Power
//==================================================

// O(log b)
ll fastPower(ll a, ll b, ll mod = MOD) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

//==================================================
// Factorials (Modulo)
//==================================================

// O(MAX)
void initCombinatorics() {
    fact[0] = 1;
    for (int i = 1; i < MAX; i++)
        fact[i] = fact[i - 1] * i % MOD;

    invFact[MAX - 1] = fastPower(fact[MAX - 1], MOD - 2);

    for (int i = MAX - 2; i >= 0; i--)
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
}

//==================================================
// Pascal Triangle (Exact nCr)
//==================================================

// O(N^2)
void initNCR() {
    for (int i = 0; i <= NCR_MAX; i++) {
        C[i][0] = C[i][i] = 1;

        for (int j = 1; j < i; j++)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
}

//==================================================
// Without Mod
//==================================================

// O(r)
ll nCr(ll n, ll r) {
    if (r < 0 || r > n) return 0;
    if (r > n - r) r = n - r;

    ll ans = 1;
    for (ll i = 1; i <= r; i++)
        ans = ans * (n - r + i) / i;

    return ans;
}

// O(1) after initNCR()
// Works only for n <= NCR_MAX and values that fit in ll.
ll nCrPrecomputed(int n, int r) {
    if (r < 0 || r > n || n > NCR_MAX) return 0;
    return C[n][r];
}

// O(r)
ll nPr(ll n, ll r) {
    if (r < 0 || r > n) return 0;

    ll ans = 1;
    while (r--)
        ans *= n--;

    return ans;
}

//==================================================
// Mod
//==================================================

// O(1)
ll nCrMod(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}

// O(1)
ll nPrMod(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[n - r] % MOD;
}
