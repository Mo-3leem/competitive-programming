template <typename T>
struct Prefix2D {
  int n, m;
  vector<vector<T>> pref;

  Prefix2D() {}

  Prefix2D(int n, int m) {
    init(n, m);
  }

  void init(int n, int m) {
    this->n = n;
    this->m = m;
    pref.assign(n + 1, vector<T>(m + 1, 0));
  }

  void build(const vector<vector<T>>& a) {
    // a must be 1-based: a[1..n][1..m]
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        pref[i][j] = a[i][j]
                   + pref[i - 1][j]
                   + pref[i][j - 1]
                   - pref[i - 1][j - 1];
      }
    }
  }

  T get(int x1, int y1, int x2, int y2) {
    // returns sum of rectangle from (x1, y1) to (x2, y2)
    return pref[x2][y2]
         - pref[x1 - 1][y2]
         - pref[x2][y1 - 1]
         + pref[x1 - 1][y1 - 1];
  }
};
