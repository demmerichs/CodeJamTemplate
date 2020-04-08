diff --git a/CodeJam/Main.cpp b/examples/2020/KS_A/C/Main.cpp
index 0493fca..4bd54c3 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/KS_A/C/Main.cpp
@@ -828,11 +828,56 @@ namespace task {
 void init(){
 }
 
+ll N, K;
+v(ll) dAi;
+
 void readInput(){
+    dAi.clear();
+    cin >> N >> K;
+    ll last, t;
+    cin >> last;
+    forn(i, N-1){
+        cin >> t;
+        dAi.pb(t-last);
+        last = t;
+    }
+    sort(all(dAi));
+}
+
+bool difficulty_possible(ll difficulty){
+    llog("difficulty", difficulty);
+    ll left_K = K;
+    forn(i, dAi.sz){
+        ll j = dAi.sz - i - 1;
+        ll cur_diff = dAi[j];
+        // after_diff = ceil(cur_diff / (cur_k + 1)) <= difficulty
+        // => cur_k >= cur_diff / difficulty - 1
+        // => min cur_k = ceil(cur_diff / difficulty) - 1
+        // cur_diff, difficulty, cur_k
+        // 13, 20, 0
+        // 19, 20, 0
+        // 20, 20, 0
+        // 21, 20, 1
+        left_K -= max<ll>(0,ceill(cur_diff, difficulty) - 1);
+        if(left_K < 0){
+            llog(dAi);
+            llog("not enough K", left_K, j);
+            return false;
+        }
+        if(cur_diff <= difficulty){
+            llog(dAi);
+            llog("enough K", left_K, j);
+            return true;
+        }
+    }
+    llog(dAi);
+    llog("enough K?", left_K);
+    return left_K >= 0;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = binSearchDisc<bool>(true, difficulty_possible, dAi.bk, 1);
 }
 
 } // namespace task
