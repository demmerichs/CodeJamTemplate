diff --git a/CodeJam/Main.cpp b/examples/2020/KS_A/B/Main.cpp
index 9a2018d..5d2a3a7 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/KS_A/B/Main.cpp
@@ -1411,11 +1411,41 @@ void init(){
     cin >> T;
 }
 
+ll N, K, P;
+v(v(ll)) bnk;
+
 void readInput(){
+    cin >> N >> K >> P;
+    ll t;
+    bnk.cl;
+    forn(n, N){
+        bnk.pb(v(ll)());
+        bnk.bk.pb(0);
+        ll s = 0;
+        forn(k, K){
+            cin >> t;
+            s += t;
+            bnk.bk.pb(s);
+        }
+        forn(_, P-K){
+            bnk.bk.pb(s);
+        }
+    }
+    llog("bnk", bnk);
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    v(v(ll)) dp(N+1, v(ll)(P+1, 0));
+    fornn(n, 1, N+1){
+        fornn(p, 1, P+1){
+            forn(s, p+1){
+                dp[n][p] = max(dp[n][p], dp[n-1][s] + bnk[n-1][p-s]);
+            }
+        }
+    }
+    llog("dp", dp);
+    result = dp[N][P];
 }
 
 } // namespace task
