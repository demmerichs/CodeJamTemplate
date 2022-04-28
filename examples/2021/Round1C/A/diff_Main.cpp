diff --git a/CodeJam/Main.cpp b/examples/2021/Round1C/A/Main.cpp
index a7f0d62..4831678 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/Round1C/A/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE ld
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1501,11 +1501,31 @@ void init(){
     cin >> T;
 }
 
+ll N, K;
+v(ll) Pi;
+
 void readInput(){
+    cin >> N >> K;
+    Pi.resize(N);
+    forn(i, N) cin >> Pi[i];
+    sort(all(Pi));
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    v(ll) winners;
+    lg(Pi);
+    forn(i, N-1){
+        winners.pb((Pi[i+1]-Pi[i])/2);
+        winners.pb(Pi[i+1]-Pi[i]-1 - winners.bk);
+    }
+    winners.pb(Pi[0]-1);
+    winners.pb(K-Pi[N-1]);
+    sort(all(winners));
+    reverse(all(winners));
+    lg(winners);
+    ll total_winners = winners[0] + winners[1];
+    result = (ld) total_winners / (ld) K;
 }
 
 } // namespace task
