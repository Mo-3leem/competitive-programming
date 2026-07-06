vector<int> v = a;
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());

unordered_map<int,int> mp;
for (int i = 0; i < (int)v.size(); i++)
    mp[v[i]] = i;
