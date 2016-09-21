#define INF (1LL<<60)
#define endl '\n'
#define mp make_pair
//Super relaxed
pair<vector<int64_t>, vector<int64_t> > dijkstra(vector<vector<pair<int64_t,int64_t> > >& graph, int64_t u){

    vector<int64_t> dist (graph.size(), INF), prev (graph.size(), -1);
    dist[u] = 0;
    priority_queue<pair<int64_t,int64_t> > Q;
    Q.push(mp(-dist[u],u));
    vector<bool> seen (graph.size(), false);

    while(!Q.empty()){
        pair<int64_t,int64_t> p = Q.top();
        int64_t w = p.second;
        Q.pop();
        if(!seen[w]){
            seen[w] = true;
            for(auto to : graph[w]){
                if(dist[to.first] > dist[w] + to.second){
                    dist[to.first] = dist[w] + to.second;
                    prev[to.first] = w;
                    Q.push(mp(-dist[to.first],to.first));
                }
            }
        }
    }
    return  make_pair(dist,prev);
}
