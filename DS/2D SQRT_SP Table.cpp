// Square Sparse Table
// Build : O(nm log(min(n,m)))
// Query : O(1)
// Space : O(nm log(min(n,m)))
// Supports square queries only.

const int LG = 11;

template<typename T, class CMP = function<T(const T&, const T&)>>
struct SQRT_SP {
  CMP func;
  int n, m;
  vector<vector<T>> sp[LG];

  SQRT_SP(const vector<vector<T>>& a, const CMP& f) : func(f) {
    n = a.size();
    m = a[0].size();

    sp[0] = a;

    for (int k = 1; k < LG; k++) {
      int len = 1 << k;
      int h = len >> 1;

      if (len > min(n, m)) break;

      sp[k].assign(n - len + 1, vector<T>(m - len + 1));

      for (int i = 0; i + len <= n; i++) {
        for (int j = 0; j + len <= m; j++) {

          sp[k][i][j] = func(
              func(sp[k-1][i][j],
                   sp[k-1][i+h][j]),
              func(sp[k-1][i][j+h],
                   sp[k-1][i+h][j+h])
          );

        }
      }
    }
  }

  // query square:
  // top-left = (x,y)
  // side length = len
  T query(int x, int y, int len) {
    int k = __lg(len);
    int s = 1 << k;

    return func(
        func(sp[k][x][y],
             sp[k][x + len - s][y]),
        func(sp[k][x][y + len - s],
             sp[k][x + len - s][y + len - s])
    );
  }
};
