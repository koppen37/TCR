#include <iostream>
#include <vector>
using namespace std;
typedef pair<int64_t,int64_t> pii;
vector<int64_t> x;

int64_t power(int64_t base, int64_t exp){
    int64_t ans = 1;
    for(int i = 1; i <= exp; i++){
        ans *= base;
    }
    return ans;
}

int64_t get_x(int64_t i){
    if(i == 0) return 1;
    if(x[i] != -1) return x[i];
    x[i] = (power(25,i)/5)*2 + 5 * get_x(i-1);
    return x[i];
}

pii biggestexp(int64_t n){
    int64_t pow = 25, exp = 1;
    while( (pow * 25) <= n){
        pow *= 25;
        exp++;
    }
    return {pow,exp};
}

int64_t minisolve(int64_t n, int64_t p){
    int64_t ans = 0;
    for(int i = 0; i <= n; i++){
        if(i > 0 && i % 5 == 0) p++;
        if(p % 2 == 0) ans++;
    }
    return ans;
}

int64_t solve(int64_t n, int64_t p){
    int64_t ans = 0;
    if(n < 25){
        return minisolve(n,p);
    }
    pii a = biggestexp(n);
    int64_t b = a.first;
    int64_t e = a.second;
    int64_t fit = n/b;
    for(int i = 0; i < fit; i++){
        if(i > 0 && i % 5 == 0) p++;
        if(p % 2 == 0) {
            ans += get_x(e);
        } else {
            ans += power(25,e) - get_x(e);
        }
    }
    if(fit % 5 == 0) p++;
    n -= fit * b;
    ans += solve(n,p);
    return ans;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    x.assign(100,-1);
    int64_t n;
    while(cin >> n){
        if(n == -1) break;
        cout << solve(n,0) << endl;
    }
    return 0;
}
