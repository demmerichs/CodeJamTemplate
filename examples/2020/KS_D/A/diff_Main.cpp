diff --git a/CodeJam/Main.cpp b/examples/2020/KS_D/A/Main.cpp
index 6e1211d..8eb676d 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/KS_D/A/Main.cpp
@@ -1065,11 +1065,24 @@ void init(){
     cin >> T;
 }
 
+ll N;
+v(ll) Vi;
+
 void readInput(){
+    cin >> N;
+    Vi.resize(N);
+    forn(i, N) cin >> Vi[i];
+    Vi.pb(Vi.bk-1);
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+    ll curmax = Vi[0] - 1;
+    forn(i, N){
+        if(Vi[i] > curmax && Vi[i] > Vi[i+1]) result++;
+        curmax = max(Vi[i], curmax);
+    }
 }
 
 } // namespace task
