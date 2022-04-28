diff --git a/CodeJam/Main.cpp b/examples/2020/KS_B/A/Main.cpp
index fa1026d..4e4088e 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/KS_B/A/Main.cpp
@@ -1414,11 +1414,24 @@ void init(){
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
