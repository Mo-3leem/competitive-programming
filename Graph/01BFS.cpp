// Optimize from O((V + E) * log(V)) TO O(V + E) FOR 0/1 Weights
auto 01BFS = [&](int src) -> vector<long long> {
    deque<int> dq;
    vector<long long> dist(n, 1e18); // Handled to prevent overflow

    dq.push_front(src);
    dist[src] = 0;
    
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 0) {
                    dq.push_front(v);
                } else {
                    dq.push_back(v);
                }
            }
        }
    }
    return dist;
};
