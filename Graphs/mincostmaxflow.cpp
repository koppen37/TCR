#define INF (1LL<<60)

typedef pair<int64_t,int64_t> pii;

vector<vector<int64_t> > es, ecap, ecost;
vector<int64_t> pot, dist;
vector<pii> pred;

void dijkstras(int64_t s){
    int64_t N = es.size();
    priority_queue<pii> Q;
    vector<bool> seen (N,false);

    dist.assign(N,INF);
    pred.assign(N,{-1,0});

    dist[s] = 0;
    Q.push({0,s});

    while(!Q.empty()){
        int64_t cur = Q.top().second;
        Q.pop();
        if(seen[cur]) continue;
        seen[cur] = true;

        for(int i = 0; i < es[cur].size(); i++){
            int64_t t = es[cur][i],
                    c = ecost[cur][i];

            if(seen[t] || dist[cur] + c >= dist[t]) continue;
 			//Add EXTRA CHECKS here!
            if(ecap[cur][i] == 0) continue;

            dist[t] = dist[cur] + c;
            pred[t] = {cur,i};
            Q.push({-dist[t],t});
        }
    }
}























pii maxflow(int64_t s, int64_t t){
    int64_t n = es.size();
    int64_t flow = 0, cost = 0;
    pot.assign(n,0);
    vector<vector<int64_t> > me(0);
    for(int i = 0; i < n; i++){
        me.push_back(vector<int64_t> (es[i].size(), -1));
    }
    while(true){
        dijkstras(s);
        if(dist[t] == INF) break;

        //find maxadd
        int64_t maxadd = INF;
        int64_t cur = t;
        while(cur != s){
            maxadd = min(maxadd, ecap[pred[cur].first][pred[cur].second]);
            cur = pred[cur].first;
        }

        cost += (pot[t] + dist[t]) * maxadd;
        flow += maxadd;

        //Potential adjust
        for(int i = 0; i < n; i++){
            for(int j = 0; j < es[i].size(); j++){
                ecost[i][j] += dist[i] - dist[es[i][j]];
            }
            pot[i] += dist[i];
        }

        //adjust edges
        cur = t;
        while(cur != s){
            int64_t f = pred[cur].first,
                    j = pred[cur].second;
            ecap[f][j] -= maxadd;
            if(me[f][j] == -1){
                me[f][j] = es[cur].size();
                me[cur].push_back(j);
                es[cur].push_back(f);
                ecost[cur].push_back(0);
                ecap[cur].push_back(maxadd);
            } else {
                ecap[cur][me[f][j]] += maxadd;
            }
            cur = f;
        }
    }
    return {flow,cost};
}
