#define INF (1LL << 60)
#define endl '\n'
#define mp make_pair

void floyd_warshall (vector<vector<int64_t> >& dist){
    for(int64_t k = 0; k < dist.size(); k++){
        for(int64_t i = 0; i < dist.size(); i++){
            for(int64_t j = 0; j < dist.size(); j++){
                if(dist[i][k] != INF && dist[k][j] != INF){
                    if(dist[i][j] > dist[i][k] + dist[k][j]){
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }
}

/** The distance options
if(dist[u][v] == INF) cout << "Impossible" << endl;
else if(dist[u][u] != 0 || dist[v][v] != 0) cout << "-Infinity" << endl;
else cout << dist[u][v] << endl;
**/

//Solved : https://open.kattis.com/problems/allpairspath
