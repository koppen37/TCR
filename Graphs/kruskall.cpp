struct Edge{
    int64_t first, second, weight;
};

bool edge_compare(Edge l, Edge r){
    return (l.weight < r.weight);
}

vector<Edge> kruskal(vector<Edge> e, int64_t n){
    UnionFind UF((int)n);
    vector<Edge> A;
    sort(e.begin(),e.end(),edge_compare);
    for(int i = 0; i < e.size(); i++){
        Edge edge = e[i];
        int u = edge.first, v = edge.second;
        if(!UF.isSameSet(u,v)){
            A.push_back(edge);
            UF.unionSet(u,v);
        }
    }
    return A;
}

//Solved : https://open.kattis.com/problems/minspantree
