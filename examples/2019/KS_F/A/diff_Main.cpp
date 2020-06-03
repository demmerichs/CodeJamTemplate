diff --git a/CodeJam/Main.cpp b/examples/2019/KS_F/A/Main.cpp
index fabbe5f..3272d34 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2019/KS_F/A/Main.cpp
@@ -1013,11 +1013,61 @@ namespace task {
 void init(){
 }
 
+ll N, K;
+
+v(ll) Ai;
+d(ll, d(ll, ll)) Rij, Fij;
+
 void readInput(){
+    cin >> N >> K;
+    Ai.cl;
+    forn(i, N){
+        ll t;
+        cin >> t;
+        Ai.pb(t);
+    }
+    Rij.cl;
+    Fij.cl;
+}
+
+ll R(ll i, ll j){
+    lassert(i<j, "R: i is not smaller than j");
+    if(Rij.count(i) && Rij[i].count(j)){
+        return Rij[i][j];
+    }
+    d(ll, ll) counts;
+    fornn(c, i, j){
+        counts[Ai[c]]++;
+    }
+    auto it = max_element(all(counts), [](p(ll, ll) a, p(ll, ll) b){return a.nd<b.nd;});
+    Rij[i][j] = j - i - it->nd;
+    return Rij[i][j];
+}
+
+ll F(ll i, ll k){
+    if(i<=1)
+        return 0;
+    if(k==0)
+        return R(0, i);
+    lassert(k>0, "F: k is not bigger than 0");
+    if(Fij.count(i) && Fij[i].count(k)){
+        return Fij[i][k];
+    }
+    ll minval = INF;
+    forn(j, i){
+        ll curval = F(j, k-1) + R(j, i);
+        llog("curval:", curval);
+        if (curval < minval)
+            minval=curval;
+    }
+    llog("minval:", minval);
+    Fij[i][k] = minval;
+    return Fij[i][k];
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = F(N, K);
 }
 
 } // namespace task
