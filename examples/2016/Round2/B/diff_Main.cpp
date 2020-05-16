diff --git a/CodeJam/Main.cpp b/examples/2016/Round2/B/Main.cpp
index e858c1d..a1a8fa3 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2016/Round2/B/Main.cpp
@@ -4,7 +4,7 @@
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE "ERROR"
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE ld
 
 // The maintained and empty code template can be found at:
 // https://github.com/DavidS3141/CodeJamTemplate
@@ -1012,11 +1012,48 @@ namespace task {
 void init(){
 }
 
+ll N, K;
+v(ld) Pi;
+
 void readInput(){
+    cin >> N >> K;
+    Pi.cl;
+    ld tmp;
+    forn(i, N){
+        cin >> tmp;
+        Pi.pb(tmp);
+    }
+    sort(all(Pi));
+}
+
+ld tie_prob(const v(ld) &probs){
+    v(v(ld)) dp(K/2+1, v(ld)(K+1));
+    fore(y, 0, K/2){
+        dp[y][0] = 0.0;
+    }
+    dp[0][0] = 1.0;
+    fore(k, 1, K){
+        dp[0][k] = (1-probs[k-1]) * dp[0][k-1];
+        fore(y, 1, K/2){
+            dp[y][k] = probs[k-1] * dp[y-1][k-1] + (1-probs[k-1])*dp[y][k-1];
+        }
+    }
+    return dp[K/2][K];
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0.0;
+    fore(low_count, 0, K){
+        v(ld) cur_probs;
+        forn(i, low_count){
+            cur_probs.pb(Pi[i]);
+        }
+        forn(i, K-low_count){
+            cur_probs.pb(Pi[N-1-i]);
+        }
+        result = max<ld>(result, tie_prob(cur_probs));
+    }
 }
 
 } // namespace task
