//=====================================================
// Smallest Prime Factor (SPF)
// Build: O(N log log N)
// Space: O(N)
// Query Prime Factorization: O(log n)
//
// Use when:
// - Many factorization queries
//=====================================================

const int N = 1e6 + 5;
int spf[N];

void buildSPF() {
    iota(spf, spf + N, 0);

    for (int i = 2; i * i < N; i++) {
        if (spf[i] != i) continue;

        for (int j = i * i; j < N; j += i)
            if (spf[j] == j)
                spf[j] = i;
}

// return {{prime, exponent}, ...}
vector<pair<int,int>> primeFactorization(int x) {
    vector<pair<int,int>> fac;

    while (x > 1) {
        int p = spf[x];
        int cnt = 0;

        while (x % p == 0) {
            x /= p;
            cnt++;
        }

        fac.push_back({p, cnt});
    }

    return fac;
}
