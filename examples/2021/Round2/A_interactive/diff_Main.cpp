diff --git a/CodeJam/Main.cpp b/examples/2021/Round2/A_interactive/Main.cpp
index 00aa56c..87f5560 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/Round2/A_interactive/Main.cpp
@@ -1,7 +1,7 @@
 // #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
 #define DEFAULT_VAL_TRIGGER result.sz == 0
 #define DEFAULT_VAL "IMPOSSIBLE"
-// #define IA_MODE        //remove comment on this line, to activate interactive problem mode
+#define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
@@ -1540,8 +1540,10 @@ using namespace std;
 
 namespace task {
 
+ll N;
+
 void init(){
-    cin >> T;
+    cin >> T >> N;
 }
 
 void readInput(){
@@ -1549,6 +1551,24 @@ void readInput(){
 
 // write to COMM_TYPE result
 void calcFunction() {
+    forn(i, N-1){
+        v(str) q;
+        q.pb("M");
+        q.pb(to_string(i+1));
+        q.pb(to_string(N));
+        out(q);
+        ll pos = in();
+        if(pos!=i+1){
+            q.cl;
+            q.pb("S");
+            q.pb(to_string(i+1));
+            q.pb(to_string(pos));
+            out(q);
+            in();
+        }
+    }
+    out("D");
+    in();
 }
 
 } // namespace task
