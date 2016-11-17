#define INF (1<<30)

struct Node {
    int match, deg, id;
    set<int> adj;

    bool operator<(const Node& rhs) const{
        if(deg == rhs.deg) return id > rhs.id;
        else return deg > rhs.deg;
    }
};

vector<Node> U, V;
vector<int> dist;

bool bfs() {
    queue<int> Q;
    for(int i = 1; i < U.size(); i++) {
        if(U[i].match == 0) {
            dist[i] = 0;
            Q.push(i);
        } else {
            dist[i] = INF;
        }
    }
    dist[0] = INF;
    while(!Q.empty()) {
        int i = Q.front();
        Q.pop();
        if(dist[i] < dist[0]) {
            for(const int &j : U[i].adj) {
                if(dist[V[j].match] == INF) {
                    dist[V[j].match] = dist[i] + 1;
                    Q.push(V[j].match);
                }
            }
        }
    }
    return dist[0] != INF;
}

bool dfs(int i) {
    if(i != 0) {
        for(const int &j : U[i].adj) {
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

int hopcroft_karp() {
    int matching = 0;
    while(bfs()) {
        for(int i = 1; i < U.size(); i++) {
            if(U[i].match == 0) {
                if(dfs(i)) {
                    matching++;
                }
            }
        }
    }
    return matching;
}
