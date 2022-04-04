diff --git a/CodeJam/Main.cpp b/examples/2020/KS_C/D/Main.cpp
index 6e1211d..ce6ecb3 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/KS_C/D/Main.cpp
@@ -1065,11 +1065,89 @@ void init(){
     cin >> T;
 }
 
+const ll MAXLOG2N = 18;
+ll N, Q;
+v(ll) Ai;
+v(bool) update;
+v(p(ll,ll)) oparams;
+
+v(ll) as_st, ias_st;
+
 void readInput(){
+    cin >> N >> Q;
+    Ai.resize(N);
+    as_st.assign(1<<(MAXLOG2N+1), 0);
+    ias_st.assign(1<<(MAXLOG2N+1), 0);
+    update.resize(Q);
+    oparams.resize(Q);
+
+    forn(i, N) cin >> Ai[i];
+
+    forn(i, Q){
+        char type;
+        ll a,b;
+        cin >> type >> a >> b;
+        update[i] = type=='U';
+        oparams[i] = mp(a,b);
+    }
+}
+
+void up(ll &treeidx){
+    treeidx--;
+    treeidx/=2;
+}
+
+void update_tree(ll idx, ll val){
+    ll curidx = idx + (1<<MAXLOG2N) - 1;
+    ll as_val = (idx&1)?-val:val;
+    ll ias_val = as_val * (idx+1);
+    ll as_del = as_val - as_st[curidx];
+    ll ias_del = ias_val - ias_st[curidx];
+    curidx*=2;
+    curidx++;
+    do{
+        up(curidx);
+        as_st[curidx] += as_del;
+        ias_st[curidx] += ias_del;
+    }while(curidx > 0);
+}
+
+cell recur_query_tree(ll node, ll nl, ll nr, ll l, ll r){
+    llog("recur_query_tree");
+    lg(node);
+    lg(nl);
+    lg(nr);
+    lg(l);
+    lg(r);
+    llog("");
+    if(l>r) return cell(0, 0);
+    if(l==nl && r==nr) return cell(as_st[node], ias_st[node]);
+    ll nm = (nl+nr)/2;
+    return recur_query_tree(node*2+1, nl, nm, l, min(r, nm)) + recur_query_tree(node*2+2, nm+1, nr, max(l, nm+1), r);
+}
+
+ll query_tree(ll l, ll r){
+    cell q = recur_query_tree(0, 0, (1<<MAXLOG2N) - 1, l, r);
+    lg(l);
+    lg(r);
+    lg(q);
+    ll as = q.real();
+    ll ias = q.imag();
+    if(l&1){
+        as*=-1;
+        ias*=-1;
+    }
+    return ias - l * as;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+    forn(i, N) update_tree(i, Ai[i]);
+    forn(i, Q){
+        if(update[i]) update_tree(oparams[i].st-1, oparams[i].nd);
+        else result += query_tree(oparams[i].st-1, oparams[i].nd-1);
+    }
 }
 
 } // namespace task
