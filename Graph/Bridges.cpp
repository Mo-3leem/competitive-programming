// Tarjan Bridge Algorithm, A bridge is an edge whose removal increases the number of connected components.
// Time: O(N + M)
// Space: O(N + M)

int n;
vector<vector<int>> adj;

vector<bool> visited;
vector<int> tin, low;
int timer;
vector<pair<int, int>> bridges;

void dfs(int v, int p = -1) {
  visited[v] = true;
  tin[v] = low[v] = timer++;
  for (int to: adj[v]) {
    if (to == p) continue;
    if (visited[to]) {
      low[v] = min(low[v], tin[to]);
    } else {
      dfs(to, v);
      low[v] = min(low[v], low[to]);
      if (low[to] > tin[v])
        bridges.push_back({v, to});
    }
  }
}
int comp;

void find_bridges() {
  timer = 0;
  comp = 0;
  bridges.clear();
  visited.assign(n, false);
  tin.assign(n, -1);
  low.assign(n, -1);
  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      comp++;
      dfs(i);
    }
  }
}
