#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <climits>

using namespace std;

bool bfs(const vector<vector<int> > &graph, int s, int t, vector<int> &parents) {
    int n = graph.size();
    vector<bool> seen(n);

    queue<int> q;
    q.push(s);
    seen[s] = true;
    parents[s] = -1;

    while(!q.empty()) {
        int u = q.front();
        q.pop();
        
        for(int v = 0; v < n; v++) {
            if(seen[v] || graph[u][v] <= 0) continue;
            q.push(v);
            parents[v] = u;
            seen[v] = true;
        }
    }

    return (seen[t] == true);
}

int ford_fulkerson(vector<vector<int> > &resid, int s, int t) {
    int n = resid.size(), max_flow = 0;
    vector<int> parents(n);

    while(bfs(resid, s, t, parents)) {
        int path_flow = INT_MAX;
        for(int v = t; v != s; v = parents[v]) {
            path_flow = min(path_flow, resid[parents[v]][v]);
        }
        
        for(int v = t; v != s; v = parents[v]) {
            resid[parents[v]][v] -= path_flow;
            resid[v][parents[v]] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}


int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<vector<int> > graph(n, vector<int>(n, 0));
    
    for(int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        graph[u][v] = c;
    } 
    
    vector<vector<int> > resid(graph.begin(), graph.end());
    int max_flow = ford_fulkerson(resid, s, t), used = 0;   
    
    for(int u = 0; u < n; u++) for(int v = 0; v < n; v++) {
        int f = graph[u][v] - resid[u][v];
        if(f > 0) used++;
    }   
 
    cout << n << " " << max_flow << " " << used << endl;
    for(int u = 0; u < n; u++) for(int v = 0; v < n; v++) {
        int f = graph[u][v] - resid[u][v];
        if(f > 0) cout << u << " " << v << " " << f << endl;
    }

    return 0;
}
