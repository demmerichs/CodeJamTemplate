diff --git a/CodeJam/Main.cpp b/examples/2022/Qualification/C/Main.cpp
index f8bdafd..049f151 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2022/Qualification/C/Main.cpp
@@ -1568,11 +1568,32 @@ void init(){
     cin >> T;
 }
 
+ll N;
+v(ll) Si;
+
 void readInput(){
+    cin >> N;
+    Si.resize(N);
+    forn(i, N)
+        cin >> Si[i];
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    v(ll) counts(N, 0);
+    forn(i, N){
+        counts[min(Si[i], N)-1]++;
+    }
+    lg(counts);
+    forn(i, N-1){
+        ll j = N-i-2;
+        counts[j] += counts[j+1];
+    }
+    lg(counts);
+    result = N;
+    forn(i, counts.sz){
+        result = min(result, counts[i]+i);
+    }
 }
 
 } // namespace task
