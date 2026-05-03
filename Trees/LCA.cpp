/*
  How to use
  LCA tree(n, adj);
  tree.lca(u, v);
*/
struct LCA {
  int n, LOG;
  vector<vector<int> > up, adj;
  vector<int> depth;

  LCA(int n, vector<vector<int> > &g, int root = 0) {
    this->n = n;
    adj = g;
    LOG = __lg(n) + 1;

    up.assign(n, vector<int>(LOG));
    depth.assign(n, 0);

    dfs(root, root);
  }

  void dfs(int u, int par) {
    up[u][0] = par;

    for (int j = 1; j < LOG; j++) {
      up[u][j] = up[up[u][j - 1]][j - 1];
    }

    for (auto &v: adj[u]) {
      if (v == par) continue;

      depth[v] = depth[u] + 1;
      dfs(v, u);
    }
  }

  int kthAncestor(int u, int k) {
    for (int j = 0; j < LOG; j++) {
      if (k & (1 << j)) {
        u = up[u][j];
      }
    }
    return u;
  }

  int lca(int u, int v) {
    if (depth[u] < depth[v])
      swap(u, v);

    u = kthAncestor(u, depth[u] - depth[v]);

    if (u == v)
      return u;

    for (int j = LOG - 1; j >= 0; j--) {
      if (up[u][j] != up[v][j]) {
        u = up[u][j];
        v = up[v][j];
      }
    }

    return up[u][0];
  };

  int dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
  }
};
