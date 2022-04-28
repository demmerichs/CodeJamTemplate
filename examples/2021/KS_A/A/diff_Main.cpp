diff --git a/CodeJam/Main.cpp b/examples/2021/KS_A/A/Main.cpp
index fa1026d..4856e6d 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/KS_A/A/Main.cpp
@@ -1414,11 +1414,21 @@ void init(){
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
