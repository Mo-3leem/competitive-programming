// ============================================================================
// Tree Hashing (Rooted Tree)
// ----------------------------------------------------------------------------
// Time Complexity: O(n log n)
//
// Computes a ID (hash) for every subtree in a ROOTED tree.
//
// hash[u] = unique ID representing the SHAPE of the subtree rooted at u

// Notes:
//   - Node labels/values are ignored; only the tree structure matters.
//   - Child order matters by default.
//     Uncomment sort(child.begin(), child.end()) if children are unordered.

// Usage:
//   mp.clear();
//   vector<int> hash(n + 1);
//   tree_hash(root, -1, hash, adj);

// IMPORTANT:
//   - Call mp.clear() before each test case.
//   - If comparing TWO trees, DO NOT clear mp between the two DFS calls;
//     both trees must use the same map.

map<vector<int>, int> mp;

void tree_hash(int u, int p, vector<int> &hash, vector<vector<int>> &adj) {
    vector<int> child;
    for (auto &v : adj[u]) {
        if (v != p) {
            tree_hash(v, u, hash, adj);
            child.emplace_back(hash[v]);
        }
    }

    // Uncomment the following line if the order of children doesn't matter
    // sort(child.begin(), child.end());

    // insert your self in the child array to hash the full subtree
    if (!mp.count(child)) {
        mp[child] = mp.size() + 1;
    }
    hash[u] = mp[child];
}
