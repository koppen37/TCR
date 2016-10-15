int64_t gcd(int64_t a, int64_t b) { while(b) {a %= b; swap(a,b); } return a; }
int64_t lcm(int64_t a, int64_t b) { return (a / gcd(a, b)) * b; }
int64_t mod(int64_t a, int64_t b) { return ((a % b) + b) % b; }
 
//find x, y, s.t. ax + by = d = gcd(a,b)
void extended_euclid(int64_t a, int64_t b, int64_t& x, int64_t& y, int64_t& d){
    int64_t xx = y = 0;
    int64_t yy = x = 1;
    while(b) {
        int64_t q = a / b;
        int64_t t = b; b = a % b; a = t;
        t = xx; xx = x - q * xx; x = t;
        t = yy; yy = y - q * yy; y = t;
    }
    d = a;
    return;
}
