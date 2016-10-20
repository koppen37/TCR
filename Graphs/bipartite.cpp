vector<vector<int> > g;
vector<int> colors;

bool dfs(const int &i, const int &color) {
    if(colors[i] != 0 && colors[i] != color) {
        return false;
    }
    if(colors[i] == 0) {
        colors[i] = color;
        for(unsigned int j = 0; j < g[i].size(); j++) {
            if(!dfs(g[i][j], -color)) {
                return false;
            }
        }
    }
    return true;
}

bool bipartite(const int &p) {
	colors.assign(p,0);
    for(int i = 0; i < p; i++) {
        if(colors[i] == 0 && !dfs(i, 1)) {
            return false;
        }
    }
    return true;
}
