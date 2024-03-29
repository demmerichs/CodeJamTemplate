diff --git a/CodeJam/Main.cpp b/examples/2020/KS_D/B/Main.cpp
index 2150379..05fafcd 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/KS_D/B/Main.cpp
@@ -1570,11 +1570,34 @@ void init(){
     cin >> T;
 }
 
+ll K;
+v(ll) Ai;
+
 void readInput(){
+    cin >> K;
+    Ai.resize(K);
+    forn(i, K) cin >> Ai[i];
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+    ll countup = 0;
+    ll countdown = 0;
+    fornn(i, 1, K){
+        if(Ai[i] > Ai[i-1]){
+            countup++;
+            countdown = 0;
+        } else if(Ai[i] < Ai[i-1]){
+            countdown++;
+            countup = 0;
+        }
+        if(countup >= 4 || countdown >= 4){
+            result++;
+            countup = 0;
+            countdown = 0;
+        }
+    }
 }
 
 } // namespace task
