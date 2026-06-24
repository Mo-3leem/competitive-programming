// O(n*log(n))
const int N = 1e5 + 10;
bitset<N> bt;
vector<pair<int, int>> adj[N];

  bt.set();
  bt[0] = bt[1] = 0;
  for (int i = 2; i < N; i++) {
    if (bt[i]) {
      for (int j = i; j < N; j+=i) {
        int cnt{}, tmp = j;
        while (tmp % i == 0) tmp /= i, cnt++;
        adj[j].emplace_back(i, cnt);
      }
    }
  }
