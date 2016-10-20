const int64_t M = 1000000007;

vector<vector<int64_t> > DP(4001, vector<int64_t>(4001, -1));

int64_t binom(int64_t n, int64_t k) {
    if(k == 0 || k == n) return 1;
    if(DP[n][k] != -1) return DP[n][k];
    DP[n][k] = binom(n - 1, k - 1) + binom(n - 1, k);
    DP[n][k] %= M;
    return DP[n][k];
}
