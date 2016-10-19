#define INF (1LL<<60)

struct Edge{
    int64_t u, v, w;
};

vector<int64_t> dist;
vector<Edge> edges;

//s is the start node, n is the amount of nodes.
bool bellmanford(int64_t s, int64_t n){
    dist.clear();
    dist.resize(n,INF);
    dist[s] = 0;

    for(int64_t i = 0; i < n-1; i++){
        for(const Edge& e: edges){
            dist[e.v] = min(dist[e.v],dist[e.u] + e.w);
        }
    }

    for(const Edge& e: edge){
        if(dist[e.v] > dist[e.u] + e.w){
            return false;
        }
    }
}
