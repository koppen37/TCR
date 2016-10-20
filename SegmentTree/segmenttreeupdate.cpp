int query(int node, int L, int R, int l, int r){
    if(l > R || r < L) return 0;
	
	
    if(lazy[node].size() != 0){
        for(int i = 0; i < lazy[node].size(); i++){
            st[node] = magic(L,R,st[node],lazy[node][i]);
        }
        if(L != R){
            vector<char> a = lazy[left(node)], b = lazy[node];
            a.insert(a.end(),b.begin(),b.end());
            lazy[left(node)] = a;
            a = lazy[right(node)];
            a.insert(a.end(),b.begin(),b.end());
            lazy[right(node)] = a;
        }
        lazy[node].clear();
    }
    
    if(L >= l && R <= r) return st[node];
    
    return query(left(node),L,(L+R)/2,l,r) + query(right(node),(L+R)/2 + 1,R,l,r);
}

void update(int node, int L, int R, int l, int r, char c){

    if(lazy[node].size() != 0){
        for(int i = 0; i < lazy[node].size(); i++){
            st[node] = magic(L,R,st[node],lazy[node][i]);
        }
        if(L != R){
            vector<char> a = lazy[left(node)], b = lazy[node];
            a.insert(a.end(),b.begin(),b.end());
            lazy[left(node)] = a;
            a = lazy[right(node)];
            a.insert(a.end(),b.begin(),b.end());
            lazy[right(node)] = a;
        }
        lazy[node].clear();
    }

    if(l > R || r < L) return;
    if(L >= l && R <= r) {
        st[node] = magic(L,R,st[node],c);
        if(L != R){
            lazy[left(node)].push_back(c);
            lazy[right(node)].push_back(c);
        }
        return;
    }
    
    update(left(node),L,(L+R)/2,l,r,c);
    update(right(node),(L+R)/2 + 1, R, l,r,c);

    st[node] = st[left(node)] + st[right(node)];

}
