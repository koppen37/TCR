//Input two numbers a and b
//Return gcd(a,b)
int64_t gcd(int64_t a, int64_t b){
    if(a < b) swap(a,b);
    while(b != 0){
        int64_t r = a % b;
        a = b;
        b = r;
    }
    return a;
}

//Input two numbers a and b;
//Return triple (x,y,c) satisfying:
//x * a + y * b = c, with c = gcd(a,b)
pair<pair<int64_t,int64_t>, int64_t> egcd(int64_t a, int64_t b){
    int64_t p_prev = 0, p_cur = 1;
    int64_t q_prev = 1, q_cur = 0;
    int m = 0;
    if(a < b) {
        m++;
        swap(a,b);
        swap(q_prev,p_prev);
        swap(q_cur,p_cur);
    }
    while(b != 0){
        m++;
        int64_t r = a % b;
        int64_t k = a / b;
        int64_t s_temp = k * q_cur + q_prev;
        q_prev = q_cur, q_cur = s_temp;
        int64_t t_temp = k * p_cur + p_prev;
        p_prev = p_cur, p_cur = t_temp;
        a = b;
        b = r;
    }
    if(m % 2 == 0) m = 1;
    else m = -1;
    return make_pair(make_pair(m*q_prev,-m*p_prev),a);
}

//solved: https://open.kattis.com/problems/modulararithmetic
//https://open.kattis.com/problems/wipeyourwhiteboards
