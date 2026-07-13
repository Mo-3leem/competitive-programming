// Smallest Prime Factor (SPF)
// Must Call buildSPF()
// Build: O(N log log N)
// Factorization: O(log n)
// Divisors: O(log n + number of divisors)
// Space: O(N)

const int N = 1e6 + 5;
int spf[N];

void buildSPF() {
    iota(spf, spf + N, 0);
    for (int i = 2; i * i < N; i++)
        if (spf[i] == i)
            for (int j = i * i; j < N; j += i)
                if (spf[j] == j)
                    spf[j] = i;
}

// return {{prime, exponent}, ...}
vector<pair<int,int>> factor(int x) {
    vector<pair<int,int>> f;
    while (x > 1) {
        int p = spf[x], c = 0;
        while (x % p == 0) x /= p, c++;
        f.push_back({p, c});
    }
    return f;
}

// return all divisors (unsorted)
vector<int> divisors(int x) {
    vector<int> d{1};

    while (x > 1) {
        int p = spf[x], sz = d.size(), pw = 1;

        while (x % p == 0) {
            x /= p;
            pw *= p;
            for (int i = 0; i < sz; i++)
                d.push_back(d[i] * pw);
        }
    }

    return d;
}
