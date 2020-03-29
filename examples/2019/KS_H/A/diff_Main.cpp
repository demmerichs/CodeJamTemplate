diff --git a/CodeJam/Main.cpp b/examples/2019/KS_H/A/Main.cpp
index 4f27d32..45f8e96 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2019/KS_H/A/Main.cpp
@@ -2,7 +2,7 @@
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
 #define ERROR_WORD "IMPOSSIBLE"
-#define COMM_TYPE ll
+#define COMM_TYPE v(ll)
 #define IA_ERROR_CODE "ERROR"
 
 // The maintained and empty code template can be found at:
@@ -667,11 +667,30 @@ namespace task {
 void init(){
 }
 
+ll N;
+v(ll) cits;
+
 void readInput(){
+    cin >> N;
+    cits.clear();
+    forn(i, N){
+        ll t;
+        cin >> t;
+        cits.pb(t);
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    multiset<ll> tops;
+    result.clear();
+    forn(i, N){
+        tops.insert(cits[i]);
+        if(*tops.begin() < tops.sz){
+            tops.erase(tops.begin());
+        }
+        result.pb(tops.sz);
+    }
 }
 
 } // namespace task
