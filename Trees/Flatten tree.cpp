// val[flat[i]] = value of the node
vector<int> flat(n);
int timer = 0;
vector<int> in(n), out(n);

function<void(int, int)> dfs = [&](int u, int p) {
  in[u] = timer;
  flat[timer] = u;
  timer++;
  for (auto v: adj[u]) {
    if (v == p) continue;
    dfs(v, u);
  }
  out[u] = timer - 1;
};
dfs(0, -1);
