diff --git a/CodeJam/Main.cpp b/examples/2020/KS_B/A/Main.cpp
index fad3e96..2362f4b 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/KS_B/A/Main.cpp
@@ -1025,11 +1025,24 @@ void init(){
     cin >> T;
 }
 
+ll N;
+v(ll) Hi;
+
 void readInput(){
+    cin >> N;
+    Hi.resize(N);
+    forn(i, N) cin >> Hi[i];
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+    forn(i, N-2){
+        ll p = i;
+        ll c = i+1;
+        ll n = i+2;
+        if(Hi[p]<Hi[c] && Hi[c] > Hi[n]) result++;
+    }
 }
 
 } // namespace task
