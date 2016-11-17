typedef pair<int64_t,int64_t> pii;

vector<vector<pii> > g;
vector<int64_t> dist, prev;

int64_t prim(int64_t start){
	int64_t n = g.size();
   	dist.assign(n,INF);
    prev.assign(n,-1);
    int64_t length = 0;
    dist[start] = 0;

    priority_queue<pii> Q;
    Q.push({-dist[start],start});

    vector<bool> seen (n);

    while(!Q.empty()){
        pii p = Q.top();
        int64_t w = p.second;
        Q.pop();
        if(seen[w]) continue;
        seen[w] = true;
        length += dist[w];
        for(auto to : g[w]){
            if(!seen[to.first] && dist[to.first] > to.second){
                dist[to.first] = to.second;
                prev[to.first] = w;
                Q.push({-dist[to.first],to.first});
            }
        }
    }
    return length;
}
