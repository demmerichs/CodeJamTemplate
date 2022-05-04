diff --git a/CodeJam/Main.cpp b/examples/2021/Qualification/C/Main.cpp
index 00aa56c..e769f00 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/Qualification/C/Main.cpp
@@ -1,11 +1,11 @@
-// #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
+#define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
 #define DEFAULT_VAL_TRIGGER result.sz == 0
 #define DEFAULT_VAL "IMPOSSIBLE"
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
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
 
+ll N, C;
+
 void readInput(){
+    cin >> N >> C;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result.clear();
+    if(C<N-1)
+        return;
+    if(C>N*(N+1)/2-1)
+        return;
+    forn(i, N) result.pb(i+1);
+    forn(i, N-1){
+        ll j = N-i-2;
+        lassert(C>j, "not enough costs left");
+        ll take = min(C-j, N-j);
+        reverse(msel(result, j, j+take));
+        C -= take;
+    }
 }
 
 } // namespace task
