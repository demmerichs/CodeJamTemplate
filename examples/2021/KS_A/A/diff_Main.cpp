diff --git a/CodeJam/Main.cpp b/examples/2021/KS_A/A/Main.cpp
index 05e1aa9..f7138c0 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/KS_A/A/Main.cpp
@@ -1540,11 +1540,21 @@ void init(){
     cin >> T;
 }
 
+ll N, K;
+str S;
+
 void readInput(){
+    cin >> N >> K;
+    cin >> S;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    ll curk = 0;
+    forn(i, N/2){
+        if(S[i]!=S[N-1-i]) curk++;
+    }
+    result = abs(curk-K);
 }
 
 } // namespace task
