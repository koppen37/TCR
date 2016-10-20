#include <iostream>
#include <vector>

using namespace std;
const int64_t M = 1000000007;

vector<vector<int64_t> > DP(4001, vector<int64_t>(4001, -1));
vector<int64_t> P(4001);
vector<int64_t> B(4001);



int64_t binom(int64_t n, int64_t k) {
    if(k == 0 || k == n) return 1;
    if(DP[n][k] != -1) return DP[n][k];
    DP[n][k] = binom(n - 1, k - 1) + binom(n - 1, k);
    DP[n][k] %= M;
    return DP[n][k];
}

int64_t pin(int64_t n){
    if(n == 0 || n == 1) return 1;
    if(P[n]) return P[n];
    int64_t sum = 0;
    for(int i = 0; i < n; i++){
        sum += binom(n-1,i) * pin(n-1-i);
        sum %= M;
    }
    P[n] = sum;
    return P[n];
}

int64_t bin(int64_t n){
    if(n == 1) return 1;
    int64_t sum = 0;
    for(int i = 1; i <= n; i++){
        sum += binom(n,i) * pin(n-i);
        sum %= M;
    }
    return sum;
}

int main()
{
    int64_t n;
    cin >> n;
    cout << bin(n) << endl;

    return 0;
}
