#define INF (1LL << 60)

struct Node {
    int64_t match, deg, id;
    set<int64_t> adj;

    bool operator<(const Node& rhs) const{
        if(deg == rhs.deg) return id > rhs.id;
        else return deg > rhs.deg;
    }
};

vector<Node> U, V;
vector<int64_t> dist;

bool bfs() {
    queue<int64_t> Q;
    for(int64_t i = 1; i < U.size(); i++) {
        if(U[i].match == 0) {
            dist[i] = 0;
            Q.push(i);
        } else {
            dist[i] = INF;
        }
    }
    dist[0] = INF;
    while(!Q.empty()) {
        int64_t i = Q.front();
        Q.pop();
        if(dist[i] < dist[0]) {
            for(const int64_t &j : U[i].adj) {
                if(dist[V[j].match] == INF) {
                    dist[V[j].match] = dist[i] + 1;
                    Q.push(V[j].match);
                }
            }
        }
    }
    return dist[0] != INF;
}

bool dfs(int64_t i) {
    if(i != 0) {
        for(const int64_t &j : U[i].adj) {
            if(dist[V[j].match] == dist[i] + 1) {
                if(dfs(V[j].match)) {
                    V[j].match = i;
                    U[i].match = j;
                    return true;
                }
            }
        }
        dist[i] = INF;
        return false;
    }
    return true;
}

int64_t hopcroft_karp() {
    int64_t matching = 0;
    dist.assign(U.size(), INF); //This is untested
    while(bfs()) {
        for(int64_t i = 1; i < U.size(); i++) {
            if(U[i].match == 0) {
                if(dfs(i)) {
                    matching++;
                }
            }
        }
    }
    return matching;
}
