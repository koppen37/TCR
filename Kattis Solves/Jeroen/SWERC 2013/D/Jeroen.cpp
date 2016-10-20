#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <stack>
using namespace std;

vector<string> ss;

string reverse_flip(string s){
    string ans;
    stack<char> st;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == 'L') st.push('R');
        if(s[i] == 'R') st.push('L');
    }
    while(!st.empty()){
        ans += st.top();
        st.pop();
    }
    return ans;
}

void fill_ss(string s, int cntdown){
    if(cntdown == 0) return;
    string ans = s;
    ans += "L";
    ans += reverse_flip(s);
    if(ans.size() >= 100) cntdown--;
    ss.push_back(ans);
    fill_ss(ans,cntdown);
    return;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int T, cs = 1;
    cin >> T;
    string start = "L";
    ss.assign(1,"");
    ss.push_back(start);
    fill_ss(start,4);
    while(T--){
        int n;
        string s;
        cin >> n >> s;
        bool ok = false;
        for(int i = 1;i <= min(n,10); i++){
            if(ss[i].find(s) < ss[i].size()){
                ok = true;
            }
        }
        cout << "Case " << cs << ": ";
        if(ok) cout << "Yes" << endl;
        else cout << "No" << endl;
        cs++;
    }
    return 0;
}
