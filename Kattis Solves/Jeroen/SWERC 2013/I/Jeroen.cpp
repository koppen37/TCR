#include <iostream>
#include <vector>
#include <set>
#include <cstdio>
#include <map>
using namespace std;

int strcnt = 1;
vector<vector<string> > words (0);
vector<pair<string,int> > cnt (0);
map<string,int> m;
set<string> s;

void make_set(int days){
    for(const string &w : words[days]){
        if(!m[w]){
            m[w] = strcnt;
            cnt.push_back({w,1});
            s.insert(w);
            strcnt++;
        } else {
            int pos = m[w];
            cnt[pos].second++;
            if(cnt[pos].second == 1){
                s.insert(w);
            }
        }
    }
    int d = days - 7;
    if(d >= 0){
        for(const string &w: words[d]){
            int pos = m[w];
            cnt[pos].second--;
            if(cnt[pos].second == 0){
                s.erase(w);
            }
        }
    }
}

void print_top(int N){
    set<int> t;
    for(const string &w : s){
        t.insert(-cnt[m[w]].second);
    }
    int i = 0;
    cout << "<top " << N << ">" << endl;
    for(const int &k : t){
        if(i >= N) break;
        for(const string &w : s){
            if(cnt[m[w]].second == -k){
                cout << w << " " << -k << endl;
                i++;
            }
        }
    }
    cout << "</top>" << endl;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    //freopen("2.in","r",stdin);
    //freopen("2.myout","w",stdout);
    int days = 0, N;
    cnt.push_back({"",0}); //offset by 1.
    string w;
    while(cin >> w){
        //cout << w << endl;
        if(w == "<top"){
            cin >> N;
            print_top(N);
            cin >> w;
        } else {
            words.push_back(vector<string> ());
            cin >> w;
            while(w != "</text>"){
                if(w.size() >= 4){
                    words[days].push_back(w);
                }
                //cout << w << endl;
                cin >> w;
            }
            make_set(days);
            //cout << w << endl;
            days++;
        }
    }
    return 0;
}
