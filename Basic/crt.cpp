// Chinese remainder theorem: finds z s.t. z % xi = ai. z is
// unique modulo M = lcm(xi). Returns (z, M), m = -1 on failure.

int64_t mod(int64_t a, int64_t b) { return ((a % b) + b) % b; }

typedef pair<int64_t,int64_t> pii;

pii crm(int64_t x1, int64_t a1, int64_t x2, int64_t a2) {
    int64_t s, t, d;
    extended_euclid(x1, x2, s, t, d);
    if (a1 % d != a2 % d) return pii(0, -1);
    return pii(mod(s * a2 * x1 + t * a1 * x2, x1 * x2) / d, x1 * x2 / d);
}

pii crm(const vector<int64_t> &x, const vector<int64_t> &a){
    pii ret = pii(a[0], x[0]);
    for (size_t i = 1; i < x.size(); ++i) {
        ret = crm(ret.second, ret.first, x[i], a[i]);
        if (ret.second == -1) break;
    }
    return ret;
}

//Credits to RagnarGrootKoerkamp
