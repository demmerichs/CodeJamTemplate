diff --git a/CodeJam/Main.cpp b/examples/2021/KS_G/A/Main.cpp
index 9a2018d..1a11798 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/KS_G/A/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1411,11 +1411,39 @@ void init(){
     cin >> T;
 }
 
+ll N, D, C, M;
+str S;
+
 void readInput(){
+    cin >> N >> D >> C >> M;
+    cin >> S;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    while(S[S.sz-1] == 'C'){
+        S = S.substr(0,S.sz-1);
+        N--;
+    }
+    result = "YES";
+    forn(i, N){
+        if(S[i] == 'C'){
+            if(C==0){
+                result="NO";
+                break;
+            } else {
+                C--;
+            }
+        } else {
+            if(D==0){
+                result = "NO";
+                break;
+            } else {
+                D--;
+                C+=M;
+            }
+        }
+    }
 }
 
 } // namespace task
