//=====================================================
// Get All Divisors
// Requires:
//      buildSPF()
//      primeFactorization()
// Time:
//      O(number of divisors)
//=====================================================

vector<int> getDivisors(int x) {

    auto fac = primeFactorization(x);

    vector<int> divs = {1};

    for (auto [p, cnt] : fac) {

        int sz = divs.size();
        int cur = 1;

        for (int i = 1; i <= cnt; i++) {
            cur *= p;

            for (int j = 0; j < sz; j++)
                divs.push_back(divs[j] * cur);
        }
    }

    sort(divs.begin(), divs.end());   // optional

    return divs;
}
