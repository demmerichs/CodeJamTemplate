diff --git a/CodeJam/Main.cpp b/examples/2021/KS_A/A/Main.cpp
index 6e1211d..172d596 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/KS_A/A/Main.cpp
@@ -1065,11 +1065,21 @@ void init(){
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
