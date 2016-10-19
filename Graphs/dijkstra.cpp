#define INF (1LL<<60)
#define endl '\n'
#define mp make_pair

typedef pair<int64_t,int64_t> pii;

vector<int64_t> dist, prev;
vector<vector<pii> > g;

void dijkstra(int64_t u){
	int64_t n = g.size();
	dist.assign(n,INF);
	prev.assign(n, -1);
    dist[u] = 0;
    priority_queue<pii> Q;
    Q.push({-dist[u],u});
    vector<bool> seen (n);

    while(!Q.empty()){
        pii p = Q.top();
        int64_t w = p.second;
        Q.pop();
        if(seen[w]) continue;
	    seen[w] = true;
        for(auto to : graph[w]){
        
        	if(seen[to.first] || dist[to.first] <= dist[w] + to.second) 
        		continue;
        		
            dist[to.first] = dist[w] + to.second;
            prev[to.first] = w;
            Q.push({-dist[to.first],to.first});
        }
    }
}

//Since edit 19/10/2016 not tested.
//Solved : https://open.kattis.com/problems/shortestpath1
//http://codeforces.com/problemset/problem/20/C
//http://www.spoj.com/problems/SHPATH/
