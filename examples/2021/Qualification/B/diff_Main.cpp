diff --git a/CodeJam/Main.cpp b/examples/2021/Qualification/B/Main.cpp
index 6e1211d..44c056c 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/Qualification/B/Main.cpp
@@ -1065,11 +1065,43 @@ void init(){
     cin >> T;
 }
 
+ll X, Y;
+str S;
+
 void readInput(){
+    cin >> X >> Y;
+    cin >> S;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+    ll lastC_opt = INF/2;
+    ll lastJ_opt = INF/2;
+    if(S[0] == 'C' || S[0] == '?') lastC_opt = 0;
+    if(S[0] == 'J' || S[0] == '?') lastJ_opt = 0;
+    lg(S);
+    lg(0);
+    lg(lastC_opt);
+    lg(lastJ_opt);
+    fornn(i, 1, S.sz){
+        ll oldC = lastC_opt;
+        ll oldJ = lastJ_opt;
+        if(S[i]=='?'){
+            lastC_opt = min(oldC, oldJ + Y);
+            lastJ_opt = min(oldJ, oldC + X);
+        } else if(S[i] == 'C'){
+            lastC_opt = min(oldC, oldJ + Y);
+            lastJ_opt = INF/2;
+        } else if(S[i] == 'J'){
+            lastJ_opt = min(oldJ, oldC + X);
+            lastC_opt = INF/2;
+        }
+        lg(i);
+        lg(lastC_opt);
+        lg(lastJ_opt);
+    }
+    result = min(lastJ_opt, lastC_opt);
 }
 
 } // namespace task
