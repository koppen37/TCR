#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

vector<vector<int> > g;
vector<int> gc;
bool done = false;
int colored = 0, pos = 0;

bool color(){
    if(pos >= g.size()) return true;
    if(gc[pos] == 0 || gc[pos] >= 5) gc[pos] = 1;
    while(gc[pos] <= 4){
        bool ok = true;
        for(int i = 0 ; i < g[pos].size(); i++){
            if(gc[pos] == gc[g[pos][i]]) ok = false;
        }
        if(ok){
            pos++;
            bool yes = color();
            if(yes) return true;
            pos--;
        }
        gc[pos]++;
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    //freopen("in.txt","r",stdin);
    int n;
    cin >> n;
    vector<vector<bool> > seen (n, vector<bool> (n, false));
    g.assign(n, vector<int> ());
    gc.assign(n, 0);
    int a, b;
    char c;
    while(cin >> a >> c >> b){
        a--; b--;
        if(seen[a][b]) continue;
        else{
            seen[a][b] = true;
            seen[b][a] = true;
            g[a].push_back(b);
            g[b].push_back(a);
        }
    }
    color();
    for(int i = 0; i < n; i++){
        cout << i + 1 << " " << gc[i] << endl;
    }

    return 0;
}
