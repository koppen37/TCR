bool dfs(const vector<vector<int> > &graph, vector<int>& colors, const int &i, const int &color) {
    if(colors[i] != 0 && colors[i] != color) {
        return false;
    }
    if(colors[i] == 0) {
        colors[i] = color;
        for(unsigned int j = 0; j < graph[i].size(); j++) {
            if(!dfs(graph, colors, graph[i][j], -color)) {
                return false;
            }
        }
    }
    return true;
}

bool bipartite(const vector<vector<int> > &graph, const int &p) {
    vector<int> colors(p, 0);
    for(int i = 0; i < p; i++) {
        if(colors[i] == 0 && !dfs(graph, colors, i, 1)) {
            return false;
        }
    }
    return true;
}
