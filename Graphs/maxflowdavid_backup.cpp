#define INF (1LL<<60)
typedef pair<int64_t,int64_t> pii;
 
vector<pii> from;
vector<vector<int64_t> > edges, edgecost;
vector<int64_t> dist;
 
void dijkstras(int64_t s){
    int64_t n = edges.size();
    dist.assign(n,0);
    from.assign(n,{-1,0});
    vector<bool> seen (n,false);
    priority_queue<pii> Q;
    dist[s] = INF;
    Q.push({0,s});
 
    while(!Q.empty()){
        int64_t cur = Q.top().second;
        Q.pop();
        if(seen[cur]) continue;
        seen[cur] = true;
 
        for(int i = 0; i < edges[cur].size(); i++){
            int64_t t = edges[cur][i],
                    c = edgecost[cur][i];
 
            if(seen[t] || min(dist[cur],c) <= dist[t]) continue;
 
            dist[t] = min(dist[cur],c);
            from[t] = {cur,i};
            Q.push({dist[t],t});
        }
    }
}
 
int64_t maxflow(int64_t s, int64_t t){
    int64_t n = edges.size();
    int64_t flow = 0;
    vector<vector<int64_t> > medge(0);
    for(int i = 0; i < n ; i++){
        medge.push_back(vector<int64_t> (edges[i].size(), -1));
    }
 
    while(true){
        dijkstras(s);
 
        if(dist[t] == 0) break;
        flow += dist[t];
 
        int64_t cur = t;
        while(cur != s){
            int64_t f = from[cur].first;
            int64_t j = from[cur].second;
            edgecost[f][j] -= dist[t];
            if(medge[f][j] == -1){
                medge[f][j] = edges[cur].size();
                medge[cur].push_back(j);
                edges[cur].push_back(f);
                edgecost[cur].push_back(dist[t]);
            } else {
                edgecost[cur][medge[f][j]] += dist[t];
            }
            cur = f;
        }
    }
    return flow;
}
