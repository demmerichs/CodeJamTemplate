diff --git a/CodeJam/Main.cpp b/examples/2021/KS_B/A/Main.cpp
index 00aa56c..9cf5b98 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/KS_B/A/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE v(ll)
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1544,11 +1544,27 @@ void init(){
     cin >> T;
 }
 
+ll N;
+
 void readInput(){
+    cin >> N;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result.resize(N);
+    char last = 0;
+    ll c = 0;
+    char n;
+    forn(i, N){
+        cin >> n;
+        if(last < n){
+            c++;
+        } else
+            c=1;
+        last = n;
+        result[i] = c;
+    }
 }
 
 } // namespace task
