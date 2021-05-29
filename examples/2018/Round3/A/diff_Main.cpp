diff --git a/CodeJam/Main.cpp b/examples/2018/Round3/A/Main.cpp
index 883b228..a9abcb8 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2018/Round3/A/Main.cpp
@@ -1065,11 +1065,32 @@ void init(){
     cin >> T;
 }
 
+ll N;
+v(ll) Ri, Ci;
+
 void readInput(){
+    cin >> N;
+    Ri.assign(N, 0);
+    Ci.assign(N, 0);
+    forn(i, N){
+        cin >> Ri[i] >> Ci[i];
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    ll minr, maxr, minc, maxc;
+    minr = maxr = Ri[0];
+    minc = maxc = Ci[0];
+    forn(i, N){
+        minr = min(minr, Ri[i]);
+        maxr = max(maxr, Ri[i]);
+        minc = min(minc, Ci[i]);
+        maxc = max(maxc, Ci[i]);
+    }
+    result = max(maxr-minr, maxc-minc);
+    result = ceill(result, 2);
+    lg(result);
 }
 
 } // namespace task
