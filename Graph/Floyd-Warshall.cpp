// ============================================================
// Floyd-Warshall - All Pairs Shortest Path
//
// After floyd():
//   adj[u][v] = shortest distance from u to v
//
// Works with:
//   - Directed / Undirected graphs
//   - Negative edges
//   - Does NOT work if shortest paths are affected by negative cycles
//
// Time:   O(N^3)
// Memory: O(N^2)
//
// HOW TO USE:
//   1) Set adj[i][j] = INF
//   2) Add edges to adj[u][v]
//   3) Call floyd()
//   4) adj[u][v] is the shortest distance
// ============================================================

const int MAXN = 505;
const long long INF = 4e18;

int n;
long long adj[MAXN][MAXN];

void floyd() {

  for (int i = 0; i < n; ++i)
    adj[i][i] = 0;

  for (int k = 0; k < n; ++k)
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j) {
        adj[i][j] = min(
          adj[i][j],
          adj[i][k] + adj[k][j]
        );
      }
}
