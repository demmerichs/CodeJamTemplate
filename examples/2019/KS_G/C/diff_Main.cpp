diff --git a/CodeJam/Main.cpp b/examples/2019/KS_G/C/Main.cpp
index 05e1aa9..9f4e209 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2019/KS_G/C/Main.cpp
@@ -1540,11 +1540,60 @@ void init(){
     cin >> T;
 }
 
+ll N, H;
+v(ll) Ai, Bi;
+
 void readInput(){
+    cin >> N >> H;
+    Ai.cl;
+    Bi.cl;
+    ll t;
+    forn(i, N){
+        cin >> t;
+        Ai.pb(t);
+    }
+    forn(i, N){
+        cin >> t;
+        Bi.pb(t);
+    }
+}
+
+void recur(ll i, ll limit, ll AH, ll BH, v(v(ll))& possible_pairs){
+    if(i==limit){
+        possible_pairs[0].pb(AH);
+        possible_pairs[1].pb(BH);
+        return;
+    }
+    recur(i+1, limit, AH + Ai[i], BH, possible_pairs);
+    recur(i+1, limit, AH, BH + Bi[i], possible_pairs);
+    recur(i+1, limit, AH + Ai[i], BH + Bi[i], possible_pairs);
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    llog("computing poss pairs");
+    v(v(ll)) poss_pairs_half1(2);
+    v(v(ll)) poss_pairs_half2(2);
+    ll split = N/2;
+    recur(0, split, 0, 0, poss_pairs_half1);
+    recur(split, N, 0, 0, poss_pairs_half2);
+
+    BalancedRangeTree<ll> rt = BalancedRangeTree<ll>(poss_pairs_half2);
+    llog("finished constructing range tree");
+
+    result = 0;
+
+    forn(i, poss_pairs_half1[0].sz){
+        v(ll) low_limit;
+        v(ll) up_limit;
+        low_limit.pb(H-poss_pairs_half1[0][i]);
+        low_limit.pb(H-poss_pairs_half1[1][i]);
+        up_limit.pb(INF);
+        up_limit.pb(INF);
+        ll range_result = rt.get_range_count(low_limit, up_limit);
+        llog("range request:", i+1, "/", poss_pairs_half1[0].sz);
+        result += range_result;
+    }
 }
 
 } // namespace task
