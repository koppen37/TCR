pair<int64_t,int64_t> crm(int64_t x1, int64_t a1, int64_t x2, int64_t a2){
    int64_t s, t, d;
    extended_euclid(x1,x2,s,t,d);
    if( (a1 % d) != (a2 % d)) {
            //cout << "wut: " << a1 << " " << (a1 % d) << " " << a2 << " " << (a2 % d) << endl;
            return {0,-1};
    }
    int64_t x = mod(mod(a2 * (x1/d), (x1/d)*x2) * s,(x1/d)*x2);
    int64_t y = mod(mod(a1 * (x2/d), (x1/d)*x2) * t,(x1/d)*x2);
    return {mod(x + y,(x1 / d) * x2), (x1 / d) * x2};
}
