#define INF (1LL<<60)

struct Edge{
    int64_t u, v, w;
};

vector<int64_t> dist, pred;
vector<Edge> edges;

//s is the start node, n is the amount of nodes. dist[u] = -INF -> path (s to u) contains negative cycle.
//Return false if there exists a negative cycle.
bool bellmanford(int64_t s, int64_t n){
    dist.clear();
    pred.clear();
    dist.assign(n,INF);
    pred.assign(n,-1);
    dist[s] = 0;

    for(int64_t i = 0; i < n-1; i++){
        for(const Edge& e: edges){
            if(dist[e.u] == INF || dist[e.v] <= dist[e.u] + e.w) continue;
            pred[e.v] = e.u;
            dist[e.v] = min(dist[e.v],dist[e.u] + e.w);
        }
    }

    bool nonegcyc = true;
    for(int64_t i = 0; i < n-1; i++){
        for(const Edge& e: edges){
            if(dist[e.u] == INF) continue;
            if(dist[e.v] > dist[e.u] + e.w){
                dist[e.v] = -INF;
                nonegcyc = false;
            }
        }
    }
    return nonegcyc;
}
