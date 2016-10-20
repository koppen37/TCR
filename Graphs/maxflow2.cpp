#define INF (1LL<<60)
typedef pair<int64_t,int64_t> pii;

vector<pii> pred;
vector<vector<int64_t> > es, ec;
vector<int64_t> dist;

void dijkstras(int64_t s){
    int64_t n = es.size();
    dist.assign(n,0);
    pred.assign(n,{-1,0});
    vector<bool> seen (n);
    priority_queue<pii> Q;
    dist[s] = INF;
    Q.push({0,s});

    while(!Q.empty()){
        int64_t cur = Q.top().second;
        Q.pop();
        if(seen[cur]) continue;
        seen[cur] = true;

        for(int i = 0; i < es[cur].size(); i++){
            int64_t t = es[cur][i],
                    c = ec[cur][i];

            if(seen[t] || min(dist[cur],c) <= dist[t]) continue;

            dist[t] = min(dist[cur],c);
            pred[t] = {cur,i};
            Q.push({dist[t],t});
        }
    }
}

int64_t maxflow(int64_t s, int64_t t){
    int64_t n = es.size();
    int64_t flow = 0;
    vector<vector<int64_t> > me(0); //To find and create backedges in residual graph
    for(int i = 0; i < n ; i++){
        me.push_back(vector<int64_t> (es[i].size(), -1));
    }

    while(true){
        dijkstras(s);

        if(dist[t] == 0) break;
        flow += dist[t];

        int64_t cur = t;
        while(cur != s){
            int64_t f = pred[cur].first;
            int64_t j = pred[cur].second;
            ec[f][j] -= dist[t];
            if(me[f][j] == -1){
                me[f][j] = es[cur].size();
                me[cur].push_back(j);
                es[cur].push_back(f);
                ec[cur].push_back(dist[t]);
            } else {
                ec[cur][me[f][j]] += dist[t];
            }
            cur = f;
        }
    }
    return flow;
}
