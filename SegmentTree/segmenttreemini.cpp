vector<int> f,st;
//f for original array values
//st for range queries values

int left (int i){
    return (i << 1);
}

int right(int i){
    return (i << 1) + 1;
}

//rangemax query, change returns to answer different questions.
int rmq(int i, int L, int R, int l, int r){
    if(l > R || r < L) return -1;
    if(L >= l && R <= r) return st[i];
    return max( rmq(left(i), L,(L+R)/2, l,r, st), rmq(right(i),((L+R)/2)+1, R,l,r));
}

void build(int i, int L, int R){
    if(L == R){
        st[i] = f[L];
    } else {
        build(left(i),L,(L+R)/2);
        build(right(i),((L+R)/2)+1, R);
        st[i] = max(st[left(i)],st[right(i)]);
    }
}

int main()
{
    f.assign(n+1);
    st.assign(4*(n+1));
    build(1,1,n);
}
