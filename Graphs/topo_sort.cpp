vector<int> topological_sort(vector<vector<int> > &g) {
    int n = g.size();

    vector<int> in_degs(n);
    for(int u = 0; u < n; u++) for(const int &v : g[u]) {
        in_degs[v]++;
    }

    queue<int> s;
    for(int u = 0; u < n; u++) if(in_degs[u] == 0) s.push(u);

    vector<int> order;
    while(!s.empty()) {
        int u = s.front();
        s.pop();
        order.push_back(u);

        for(const int &v : g[u]) {
            in_degs[v]--;
            if(in_degs[v] == 0) s.push(v);
        }
    }

    return order;
}
