#define EXTRA_CHECK if (edgecap[cur][i] == 0) continue;
#define INF (1LL<<60)
typedef pair<int64_t,int64_t> pii;

vector<vector<int64_t> > edges, edgecap, edgecost;
vector<int64_t> pot, dist;
vector<pii> from;

void dijkstras(int64_t s){
    //cout << "Starting Dijkstras" << endl;
    int64_t N = edges.size();
    priority_queue<pii> Q;
    vector<bool> seen (N,false);

    dist.assign(N,INF);
    from.assign(N,{-1,0});

    dist[s] = 0;
    Q.push({0,s});

    while(!Q.empty()){
        int64_t cur = Q.top().second;
        //cout << cur << endl;
        Q.pop();
        if(seen[cur]) continue;
        seen[cur] = true;

        for(int i = 0; i < edges[cur].size(); i++){
            int64_t t = edges[cur][i],
                    c = edgecost[cur][i];

            if(seen[t] || dist[cur] + c >= dist[t]) continue;

            EXTRA_CHECK

            dist[t] = dist[cur] + c;
            from[t] = {cur,i};
            Q.push({-dist[t],t});
        }
    }
}

pii maxflow(int64_t s, int64_t t){
    int64_t n = edges.size();
    int64_t flow = 0, cost = 0;
    pot.assign(n,0);
    vector<vector<int64_t> > medge(0);
    for(int i = 0; i < n; i++){
        medge.push_back(vector<int64_t> (edges[i].size(), -1));
    }
    while(true){
        dijkstras(s);
        //cout << "done with dijkstras " << endl;
        if(dist[t] == INF) break;

        //cout << "find maxadd" << endl;
        //find maxadd
        int64_t maxadd = INF;
        int64_t cur = t;
        while(cur != s){
            maxadd = min(maxadd, edgecap[from[cur].first][from[cur].second]);
            cur = from[cur].first;
        }

        cost += (pot[t] + dist[t]) * maxadd;
        flow += maxadd;

        //cout << "potential adjust" << endl;
        //Potential adjust
        for(int i = 0; i < n; i++){
            for(int j = 0; j < edges[i].size(); j++){
                edgecost[i][j] += dist[i] - dist[edges[i][j]];
            }
            pot[i] += dist[i];
        }

        //cout << "adjust edges " << endl;
        //adjust edges
        cur = t;
        while(cur != s){
            int64_t f = from[cur].first,
                    j = from[cur].second;
            edgecap[f][j] -= maxadd;
            if(medge[f][j] == -1){
                medge[f][j] = edges[cur].size();
                medge[cur].push_back(j);
                edges[cur].push_back(f);
                edgecost[cur].push_back(0);
                edgecap[cur].push_back(maxadd);
            } else {
                edgecap[cur][medge[f][j]] += maxadd;
            }
            cur = f;
        }
    }
    return {flow,cost};
}
