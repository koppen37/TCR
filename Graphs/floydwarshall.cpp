#define INF (1LL << 60)

vector<int64_t> dist;

void floyd_warshall (){
	int64_t n = dist.size();
    for(int64_t k = 0; k < n; k++){
        for(int64_t i = 0; i < n; i++){
            for(int64_t j = 0; j < n; j++){
                if(dist[i][k] != INF && dist[k][j] != INF){
                    if(dist[i][j] > dist[i][k] + dist[k][j]){
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }
    
    //Extra loop for Infinite loop checks.
    //Alternative check dist[u][u] < 0 || dist[v][v] < 0;
    for(int64_t i = 0; i < n; i++){
		for(int64_t j = 0; j < n; j++){
		    for(int64_t k = 0; k < n; k++){
		        if(dist[i][k] != INF && dist[k][j] != INF && dist[k][k] < 0){
		            dist[i][j] = -INF;
		        }
		    }
    	}	
	}
}

/** The distance options
if(dist[u][v] == INF) cout << "Impossible" << endl;
else if(dist[u][u] == -INF) cout << "-Infinity" << endl;
else cout << dist[u][v] << endl;
**/

//Solved : https://open.kattis.com/problems/allpairspath
