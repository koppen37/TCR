#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int64_t n;
int64_t mod = 21092013;
vector<int64_t> nextl, nextr, dp;

int64_t get_dp(int64_t i){
    if(i > n) return 0;
    if(i == n) return 1;
    if(dp[i] != -1) return dp[i];
    dp[i] = (get_dp(nextl[i]+1) +
            get_dp(nextr[i]+1) + 1) % mod;
    return dp[i];
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int T, cs = 1;
    cin >> T;
    while(T--){
        string s, t;
        cin >> s >> t;
        stack<char> st;
        int64_t ign = 0;
        for(int i = s.size()-1; i >= 0; i--){
            if(s[i] == 'U') ign++;
            else if(ign == 0) st.push(s[i]);
            else ign--;
        }
        s = "";
        while(!st.empty()){
            s += st.top();
            st.pop();
        }
        n = t.size();
        nextl.assign(n,0);
        nextr.assign(n,0);
        dp.assign(n,-1);

        int64_t n = t.size(), nl = n, nr = n;
        for(int i = t.size()-1; i >= 0; i--){
            if(t[i] == 'L') nl = i;
            if(t[i] == 'R') nr = i;
            nextl[i] = nl;
            nextr[i] = nr;
        }
        int64_t ans = 0;
        ans += get_dp(0);
        int64_t spos = s.size()-1;
        if(spos >= 0){
            for(int i = 0; i < t.size(); i++){
                if(t[i] == 'U'){
                    if(s[spos] == 'R'){
                        ans = (ans + 1 + get_dp(nextl[i]+1)) % mod;
                    } else {
                        ans = (ans + 1 + get_dp(nextr[i]+1)) % mod;
                    }
                    spos--;
                    if(spos < 0) break;
                }
            }
        }
        cout << "Case " << cs << ": ";
        cout << ans << endl;

        cs++;
    }
    return 0;
}
