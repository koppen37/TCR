#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
using namespace std;
#define INF (1<<30)
typedef pair<int,int> pii;
vector<vector<int> > g, gc, r, rc;
vector<int> dist;
vector<pii> from;


struct Node{
    int a, b, s;
};

int weight(Node a,int M){
    int ans = 0;
    ans += (a.s/M);
    if(a.s % M != 0) ans++;
    return ans;
}

void dijkstras(int s){
    int n = g.size();
    dist.assign(n,0);
    from.assign(n,{-1,0});
    vector<bool> seen (n,false);
    priority_queue<pii> Q;
    dist[s] = INF;
    Q.push({0,s});

    while(!Q.empty()){
        int cur = Q.top().second;
        Q.pop();
        if(seen[cur]) continue;
        seen[cur] = true;

        for(int i = 0; i < g[cur].size(); i++){
            int t = g[cur][i],
                c = gc[cur][i];

            if(seen[t] || min(dist[cur],c) <= dist[t]) continue;

            dist[t] = min(dist[cur],c);
            from[t] = {cur,i};
            Q.push({dist[t],t});
        }
    }
}

int maxflow(int s, int t){
    int n = g.size(),
        flow = 0;
    vector<vector<int> > mg(0);
    for(int i = 0; i < n; i++){
        mg.push_back(vector<int> (g[i].size(), -1));
    }

    while(true){
        dijkstras(s);
        if(dist[t] == 0) break;
        flow += dist[t];

        int cur = t;
        while(cur != s){
            int f = from[cur].first,
                j = from[cur].second;
            gc[f][j] -= dist[t];
            if(mg[f][j] == -1){
                mg[f][j] = g[cur].size();
                mg[cur].push_back(j);
                g[cur].push_back(f);
                gc[cur].push_back(dist[t]);
            } else {
                gc[cur][mg[f][j]] += dist[t];
            }
            cur = f;
        }
    }
    return flow;
}

bool check(int C, int maxC){
    int n = g.size();
    int s1 = n-4, t1 = n-3, s2 = n-2, t2 = n-1;
    g = r;
    gc = rc;

    g[t1].push_back(s2);
    gc[t1].push_back(C);

    int k = maxflow(s1,t2);
    if(k == maxC){
        return true;
    } else {
        return false;
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    //freopen("in.txt","r",stdin);
    int T, cs = 1;
    cin >> T;
    while(T--){
        int N, M;
        cin >> N >> M;
        vector<Node> ns (N);
        for(int i = 0; i < N; i++){
            cin >> ns[i].a >> ns[i].b >> ns[i].s;
        }
        g.assign(2*N+4, vector<int> ());
        gc.assign(2*N+4, vector<int> ());
        int s1 = 2*N, t1 = 2*N+1, s2 = 2*N+2, t2 = 2*N+3;
        int maxC = 0;
        for(int i = 0; i < N; i++){
            g[s1].push_back(i);
            gc[s1].push_back(weight(ns[i],M));
            g[s2].push_back(N+i);
            gc[s2].push_back(INF);

            g[i].push_back(t1);
            gc[i].push_back(INF);
            g[N+i].push_back(t2);
            gc[N+i].push_back(weight(ns[i],M));

            maxC += weight(ns[i],M);
            //cout << i << " weight: " << weight(ns[i], M) << endl;
        }

        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                int c;
                cin >> c;
                if(i != j){
                    if(ns[i].b + c < ns[j].a){
                        g[i].push_back(N+j);
                        gc[i].push_back(INF);
                    }
                }
            }
        }
        r = g;
        rc = gc;
        int low = 1, high = maxC;
        while( (high - low) > 1){
            int mid = (low + high)/2;
            bool k = check(mid,maxC);
            if(k){
                high = mid;
            } else {
                low = mid;
            }
        }
        cout << "Case " << cs << ": ";
        if(check(low,maxC)) cout << low << endl;
        else cout << high << endl;
        cs++;
    }
    return 0;
}
