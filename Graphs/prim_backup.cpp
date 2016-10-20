struct Primdata {
    vector<int64_t> dist;
    vector<int64_t> prev;
    int64_t length;
};

Primdata prim(vector<vector<pair<int64_t,int64_t> > >& graph, int64_t start){
    vector<int64_t> dist (graph.size(),INF);
    vector<int64_t> prev (graph.size());
    int64_t length = 0;
    dist[start] = 0;

    priority_queue<pair<int64_t,int64_t> > Q;
    Q.push({-dist[start],start});

    vector<bool> seen (graph.size(), false);

    while(!Q.empty()){
        pair<int64_t,int64_t> p = Q.top();
        int64_t w = p.second;
        Q.pop();
        if(seen[w]) continue;
        seen[w] = true;
        length += dist[w];
        for(auto to : graph[w]){
            if(!seen[to.first] && dist[to.first] > to.second){
                dist[to.first] = to.second;
                prev[to.first] = w;
                Q.push({-dist[to.first],to.first});
            }
        }
    }
    return {dist,prev,length};
}

//Solved : https://open.kattis.com/problems/minspantree
